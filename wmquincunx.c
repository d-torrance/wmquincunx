/* wmquincunx - Window Maker dockapp displaying a bean machine
 * Copyright (C) 2017 Doug Torrance <dtorrance@piedmont.edu>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 */

#include <time.h>
#include <X11/Xlib.h>
#include <libdockapp/dockapp.h>

#define PIN_COLOR "light sea green"
#define BEAN_COLOR "red"
#define DOCKAPP_WIDTH 56
#define DOCKAPP_HEIGHT 56
#define PIN_ROWS 7
#define COLUMNS 8
#define TIMEOUT 100

GC pin_gc;
GC bean_gc;
Pixmap pixmap;
int bean_x, bean_y;
int columns[COLUMNS];
int bounce;

void init(int button, int state, int x, int y);
void bean_drop(void);

int main(int argc, char **argv)
{
	XGCValues values;
	DACallbacks eventCallbacks = {NULL,
				      init,
				      NULL, NULL, NULL, NULL,
				      bean_drop};

	srand(time(NULL));

	DAParseArguments(argc, argv, NULL, 0,
			 "Window Maker dockapp displaying a bean machine",
			 PACKAGE_STRING);
	DAInitialize(NULL, PACKAGE_NAME, DOCKAPP_WIDTH, DOCKAPP_HEIGHT,
		     argc, argv);
	DASetCallbacks(&eventCallbacks);
	DASetTimeout(TIMEOUT);

	pixmap = DAMakePixmap();

	values.foreground = DAGetColor(PIN_COLOR);
	pin_gc = XCreateGC(DADisplay, pixmap, GCForeground, &values);

	values.foreground = DAGetColor(BEAN_COLOR);
	bean_gc = XCreateGC(DADisplay, pixmap, GCForeground, &values);

	init(0, 0, 0, 0);

	DAShow();
	DAEventLoop();

	return 0;
}

void init(int button, int state, int x, int y)
{
	int i, j;

	(void) button;
	(void) state;
	(void) x;
	(void) y;
	XFillRectangle(DADisplay, pixmap, DAGC, 0, 0,
		       DOCKAPP_WIDTH, DOCKAPP_HEIGHT);

	for (i = 0; i < PIN_ROWS; i++) {
		for (j = 0; j <= i; j++) {
			XFillRectangle(DADisplay, pixmap, pin_gc,
				       DOCKAPP_WIDTH/2 - 2*i + 4*j,
				       4*i + 2, 2, 2);
		}
	}

	for (i = 0; i < COLUMNS; i++)
		columns[i] = 0;

	bean_x = DOCKAPP_WIDTH/2;
	bean_y = 0;
	XFillRectangle(DADisplay, pixmap, bean_gc, bean_x, bean_y, 2, 2);

	bounce = 0;

	DASetPixmap(pixmap);
}

void bean_drop(void)
{
	int dx;
	static int column = 0;

	if (bean_y < 4*PIN_ROWS)
		bounce = 1 - bounce;
	else
		bounce = 0;

	if (bean_y == 4*PIN_ROWS)
		column = (bean_x - 14)/4;

	if (bean_y == DOCKAPP_HEIGHT - 2*columns[column] - 2) {
		bean_x = DOCKAPP_WIDTH/2;
		bean_y = 0;
		bounce = 1;
		columns[column]++;
	}

	if (bounce)
		dx = 4*(rand() % 2) - 2;
	else
		dx = 0;

	bean_x += dx;
	bean_y += 2;

	XFillRectangle(DADisplay, pixmap, bean_gc, bean_x, bean_y, 2, 2);
	XFillRectangle(DADisplay, pixmap, DAGC, bean_x - dx, bean_y - 2, 2, 2);

	DASetPixmap(pixmap);

	if (DOCKAPP_HEIGHT - 2*columns[column] == 4*PIN_ROWS)
		init(0, 0, 0, 0);
}

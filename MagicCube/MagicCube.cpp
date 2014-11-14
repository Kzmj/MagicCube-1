#pragma once 

#include "MagicCube.h"
#include "Time.h"

const GLint MagicCube::SURFACE_FRONT[CUBE_DIMENSION*CUBE_DIMENSION]
= { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
const GLint MagicCube::SURFACE_LEFT[CUBE_DIMENSION*CUBE_DIMENSION]
= { 0, 9, 18, 3, 12, 21, 6, 15, 24 };
const GLint MagicCube::SURFACE_BOTTOM[CUBE_DIMENSION*CUBE_DIMENSION]
= { 26, 17, 8, 25, 16, 7, 24, 15, 6 };
const GLint MagicCube::SURFACE_RIGHT[CUBE_DIMENSION*CUBE_DIMENSION]
= { 2, 11, 20, 5, 14, 23, 8, 17, 26 };
const GLint MagicCube::SURFACE_TOP[CUBE_DIMENSION*CUBE_DIMENSION]
= { 20, 11, 2, 19, 10, 1, 18, 9, 0 };
const GLint MagicCube::SURFACE_BACK[CUBE_DIMENSION*CUBE_DIMENSION]
= { 18, 19, 20, 21, 22, 23, 24, 25, 26 };

const GLint MagicCube::SWAP_CLOCKWISE[CUBE_DIMENSION*CUBE_DIMENSION]
= { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
const GLint MagicCube::SWAP_ANTI_CLOCKWISE[CUBE_DIMENSION*CUBE_DIMENSION]
= { 2, 5, 8, 1, 4, 7, 0, 3, 6 };

MagicCube::MagicCube() {
	center = new Point();
	eachSide = 0;
	betweenGap = 0;
	orientation = IDLE;

	for (int i = 0; i < CUBE_COUNT; ++i) {
		cubes[i] = new Cube();
	}
}

MagicCube::MagicCube(GLfloat eachSide) {
	init(Point(0, 0, 0), eachSide, 0);
}

MagicCube::MagicCube(GLfloat eachSide, GLfloat betweenGap) {
	init(Point(0, 0, 0), eachSide, betweenGap);
}

MagicCube::MagicCube(Point center, GLfloat eachSide) {
	init(center, eachSide, 0);
}

MagicCube::MagicCube(Point center, GLfloat eachSide, GLfloat betweenGap) {
	init(center, eachSide, betweenGap);
}

void MagicCube::init(Point center, GLfloat eachSide, GLfloat betweenGap) {
	this->center = new Point(center);
	this->eachSide = eachSide;
	this->betweenGap = betweenGap;
	orientation = IDLE;

	for (int i = 0; i < CUBE_DIMENSION; ++i) {
		int baseIndex = i*CUBE_DIMENSION*CUBE_DIMENSION;

		GLfloat offset = eachSide + betweenGap;
		GLfloat x = center.getX();
		GLfloat y = center.getY();
		GLfloat z = center.getZ() - offset*(i - 1);

		cubes[baseIndex + 0] = new Cube(x - offset, y + offset, z, eachSide);          // 左上
		cubes[baseIndex + 1] = new Cube(x, y + offset, z, eachSide);                   // 上
		cubes[baseIndex + 2] = new Cube(x + offset, y + offset, z, eachSide);          // 右上
		cubes[baseIndex + 3] = new Cube(x - offset, y, z, eachSide);                   // 左
		cubes[baseIndex + 4] = new Cube(x, y, z, eachSide);                            // 中
		cubes[baseIndex + 5] = new Cube(x + offset, y, z, eachSide);                   // 右
		cubes[baseIndex + 6] = new Cube(x - offset, y - offset, z, eachSide);          // 左下  
		cubes[baseIndex + 7] = new Cube(x, y - offset, z, eachSide);                   // 下
		cubes[baseIndex + 8] = new Cube(x + offset, y - offset, z, eachSide);          // 右下 
	}
}

MagicCube::~MagicCube() {
	TOOL_SAFE_DELETE(center);
	for (int i = 0; i < CUBE_COUNT; ++i) {
		TOOL_SAFE_DELETE(cubes[i]);
	}
}

void MagicCube::dispatchDraw() {
	for (int i = 0; i < CUBE_COUNT; ++i) {
		cubes[i]->dispatchDraw();
	}

	onDraw();
}

void MagicCube::onDraw() {
	// draw nothing
}

void MagicCube::startRotate(GLint orientation, GLint rotateSurface) {
	this->orientation = orientation;
	this->rotateSurface = rotateSurface;

	angle = 0;
	startMilliTime = Time::getSystemTime();
}

GLboolean MagicCube::isNeedRefresh() {
	return orientation != IDLE;
}

void MagicCube::calulateRotate() {
	INT64 currentTime = Time::getSystemTime();
	angle = (GLdouble(currentTime - startMilliTime)) / ANIMATION_DURATION*PI / 2;
	if (angle > PI / 2) angle = PI / 2;

	switch (rotateSurface) {
	case ROTATE_FRONT:   rotateFront();   break;
	case ROTATE_LEFT:    rotateLeft();    break;
	case ROTATE_BOTTOM:  rotateBottom();  break;
	case ROTATE_RIGHT:   rotateRight();   break;
	case ROTATE_TOP:     rotateTop();     break;
	case ROTATE_BACK:    rotateBack();    break;
	}
}

void MagicCube::rotateFront() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_FRONT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_FRONT[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_FRONT[i]]->rotateZ(-PI / 2, false);
				cubes[SURFACE_FRONT[i]]->rotateCenterZ(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_FRONT[i]]->rotateZ(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_FRONT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_FRONT[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_FRONT[i]]->rotateZ(PI / 2, false);
				cubes[SURFACE_FRONT[i]]->rotateCenterZ(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_FRONT[i]]->rotateZ(angle, true);
		}
	}
}

void MagicCube::rotateBack() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_BACK[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_BACK[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_BACK[i]]->rotateZ(-PI / 2, false);
				cubes[SURFACE_BACK[i]]->rotateCenterZ(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_BACK[i]]->rotateZ(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_BACK[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_BACK[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_BACK[i]]->rotateZ(PI / 2, false);
				cubes[SURFACE_BACK[i]]->rotateCenterZ(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_BACK[i]]->rotateZ(angle, true);
		}
	}
}

void MagicCube::rotateLeft() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_LEFT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_LEFT[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_LEFT[i]]->rotateX(-PI / 2, false);
				cubes[SURFACE_LEFT[i]]->rotateCenterX(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_LEFT[i]]->rotateX(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_LEFT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_LEFT[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_LEFT[i]]->rotateX(PI / 2, false);
				cubes[SURFACE_LEFT[i]]->rotateCenterX(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_LEFT[i]]->rotateX(angle, true);
		}
	}
}

void MagicCube::rotateRight() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_RIGHT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_RIGHT[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_RIGHT[i]]->rotateX(-PI / 2, false);
				cubes[SURFACE_RIGHT[i]]->rotateCenterX(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_RIGHT[i]]->rotateX(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_RIGHT[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_RIGHT[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_RIGHT[i]]->rotateX(PI / 2, false);
				cubes[SURFACE_RIGHT[i]]->rotateCenterX(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_RIGHT[i]]->rotateX(angle, true);
		}
	}
}

void MagicCube::rotateTop() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_TOP[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_TOP[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_TOP[i]]->rotateY(-PI / 2, false);
				cubes[SURFACE_TOP[i]]->rotateCenterY(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_TOP[i]]->rotateY(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_TOP[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_TOP[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_TOP[i]]->rotateY(PI / 2, false);
				cubes[SURFACE_TOP[i]]->rotateCenterY(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_TOP[i]]->rotateY(angle, true);
		}
	}
}

void MagicCube::rotateBottom() {
	if (orientation == CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_BOTTOM[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_BOTTOM[i]] = temporary[SWAP_CLOCKWISE[i]];
				cubes[SURFACE_BOTTOM[i]]->rotateY(-PI / 2, false);
				cubes[SURFACE_BOTTOM[i]]->rotateCenterY(-PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_BOTTOM[i]]->rotateY(-angle, true);
		}
	}

	if (orientation == ANTI_CLOCKWISE) {
		if (angle == PI / 2) {
			Cube* temporary[CUBE_DIMENSION*CUBE_DIMENSION];
			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				temporary[i] = cubes[SURFACE_BOTTOM[i]];
			}

			for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
				cubes[SURFACE_BOTTOM[i]] = temporary[SWAP_ANTI_CLOCKWISE[i]];
				cubes[SURFACE_BOTTOM[i]]->rotateY(PI / 2, false);
				cubes[SURFACE_BOTTOM[i]]->rotateCenterY(PI / 2);
			}

			orientation = IDLE;
			angle = 0;
		}

		for (int i = 0; i < CUBE_DIMENSION*CUBE_DIMENSION; ++i) {
			cubes[SURFACE_BOTTOM[i]]->rotateY(angle, true);
		}
	}
}




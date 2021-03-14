// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// components -- forward declaration, i.e., assume they are defined somewhere
class Transform;
class Rectangle;
class KeyBoardCtrl;
class Bounce;
class Image;
class Rotate;
class FighterCtrl;
class DeAcceleration;
class ShowAtOppositeSide;
class Follow;
class DisableOnExit;
class Gun;
class Health;
class Generations;
class FramedImage;
#define _CMPS_LIST_  \
	Transform,\
	Rectangle,\
	KeyBoardCtrl,\
	Bounce,\
	Image,\
	FighterCtrl,\
	Rotate, \
	DeAcceleration, \
	ShowAtOppositeSide,\
	Follow, \
	DisableOnExit, \
	Gun, \
	Health, \
	Generations, \
	FramedImage



// groups

struct Group_1;
struct Bullets;
#define _GRPS_LIST_  Group_1, Bullets

// handlers
struct Hdlr_1;
struct Jet;
#define _HDLRS_LIST_ Hdlr_1, Jet

#pragma once
#include "stdafx.h"
#include "Chord.h"

void Chords::DrawChords()
{
	brush.SetPen();

	Chord(hdc, x[0], y[0], x[1], y[1], xEl1, yEl1, xEl2, yEl2);
}
void Chords::DrawChords(int new_x2, int new_y2)
{
	x[1] = new_x2;
	y[1] = new_y2;
	DrawChords();
}
void Chords::DrawChords(int new_x1, int new_y1, int new_x2, int new_y2)
{
	SetStartPosition(new_x1, new_y1);
	DrawChords(new_x2,new_y2);
}

void Chords::DrawChords(int new_x1, int new_y1, int new_x2, int new_y2, int new_xEl1, int new_yEl1, int new_xEl2, int new_yEl2)
{
	SetStartPosition(new_x1, new_y1);
	SetEll(new_xEl1, new_yEl1, new_xEl2, new_yEl2);
	DrawChords(new_x2,new_y2);
}

void Chords::SetEll(int new_xEl1, int new_yEl1, int new_xEl2, int new_yEl2)
{
	xEl1 = new_xEl1;
	yEl1 = new_yEl1;
	xEl2 = new_xEl2;
	yEl2 = new_yEl2;
}

void Chords::Set_Start_Position(int new_x, int new_y)
{
	x[0]=x[1]=xEl1=xEl2= new_x;
	y[0]=y[1]=xEl1=xEl2= new_y;
}

void Chords::Set_End_Position(int new_xEl, int new_yEl)
{
	if (!Set_Rectangle)
	{
		x[1] = new_xEl;
		y[1] = new_yEl;
	}
	xEl2 = new_xEl;
	yEl2 = new_yEl;
}

void Chords::AddNewPoint(int new_xEl, int new_yEl)
{
	if (!Set_Rectangle)
	{
		x[1] = new_xEl;
		y[1] = new_yEl;
		Set_Rectangle = true;
	}
	else
	{
		xEl1 = new_xEl;
		yEl1 = new_yEl;
	}
}
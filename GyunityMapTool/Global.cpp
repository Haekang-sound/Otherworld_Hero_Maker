#include "pch.h"
#include "Global.h"

float g_tileSizeX = 144;
float g_tileSizeY = 72;

int g_mapSizeX = 20;
int g_mapSizeY = 20;

//D2D1::Matrix3x2F g_CameraPos = D2D1::Matrix3x2F::Identity();
D2D1::Matrix3x2F g_CameraPos = D2D1::Matrix3x2F::Translation(-3000,0);
float g_Scale = 1.f;
D2D1::Matrix3x2F g_CameraScale = D2D1::Matrix3x2F::Scale(1.f, 1.f);
//D2D1::Matrix3x2F g_CameraPos = D2D1::Matrix3x2F::Scale(0.5f,0.5f) * D2D1::Matrix3x2F::Translation(-3000,0);
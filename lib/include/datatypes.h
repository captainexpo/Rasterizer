#ifndef DATATYPES_H
#define DATATYPES_H
typedef struct {
  float x;
  float y;
  float z;
} float3;

typedef struct {
  float x;
  float y;
} float2;

typedef struct {
  float x;
  float y;
  float z;
  float w;
} float4;

float2 random2(float min, float max);
float3 random3(float min, float max);

float3 scalarmul3(float3 a, float scalar);
float2 scalarmul2(float2 a, float scalar);

float2 newf2(float x, float y);
float3 newf3(float x, float y, float z);
float dot3(float3 a, float3 b);
float dot2(float2 a, float2 b);
float2 add2(float2 a, float2 b);
float2 sub2(float2 a, float2 b);
float3 add3(float3 a, float3 b);
float3 sub3(float3 a, float3 b);
float2 truncate32(float3 a);
#endif

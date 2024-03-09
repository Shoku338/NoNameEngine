#include "ParticleData.h"

ParticleProp ParticleData::Explosion = {
{ 0.0f, 0.0f},                                      // Positon
{ 150.0f, 0.0f },                                   // Velocity
{ 150.0f, 150.0f },                                 // VelocityVariation
{ 255 / 255.0f, 102 / 255.0f, 34 / 255.0f, 1.0f },  // ColorBegin
{ 255 / 255.0f, 51 / 255.0f, 17 / 255.0f, 1.0f },   // ColorEnd
 15.0f,                                             // SizeBegin
 0.0f,                                              // SizeEnd
 25.0f,                                             // SizeVariation
 0.50f                                              // LifeTime

};

ParticleProp ParticleData::Gun = {
{ 0.0f, 0.0f},                                      // Positon
{ 150.0f, 0.0f },                                   // Velocity
{ 150.0f, 150.0f },                                 // VelocityVariation
{ 41 / 255.0f, 173 / 255.0f, 255 / 255.0f, 1.0f },  // ColorBegin
{ 1.0f, 1.0f, 1.0f, 1.0f },							// ColorEnd
 15.0f,                                             // SizeBegin
 0.0f,                                              // SizeEnd
 25.0f,                                             // SizeVariation
 1.0f                                               // LifeTime

};
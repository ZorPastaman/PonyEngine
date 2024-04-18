# PonyEngine
Game engine on C++ 20. Very deep WIP.

## Math

Pony Engine uses left-handed coordinate system. X is right, Y is up and Z is forward. The rotation order is ZXY (roll-pitch-yaw). The transform matrices have the next structure. The top-left matrix is a rotation-scaling matrix. The top-right column is a translation vector. The matrices are column major.

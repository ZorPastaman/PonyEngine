# PonyEngine
Game engine on C++ 23. Very deep WIP.

## Math

Pony Engine uses left-handed coordinate system. X is right, Y is up and Z is forward. The rotation order is ZXY (roll-pitch-yaw). The transform matrices have the next structure. The top-left matrix is a rotation-scaling matrix. The top-right column is a translation vector. The matrices are column major.

## License

This project is licensed under the [MIT License](LICENSE.md).

### Exceptions

Some folders contain files with their own licenses.
Each such folder has its own LICENSE file.
That license applies to the contents of that folder and all its subfolders.

#### Examples:

-The engine logo is licensed under the [CC BY 4.0 License](Logo/LICENSE.md).

When in doubt, always check for a LICENSE file inside a folder before using its content.

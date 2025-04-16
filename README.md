# How to Use

```
./ObjToRBXMesh.exe OBJ1.obj OBJ2.obj 1.00
```

You should find new files named `OBJ1.obj.mesh` and `OBJ2.obj.mesh` in the same directory.

# Build Instructions

Requisites:
1. Microsoft Build Tools
2. Visual C++ (v142 or v143)

```
git clone https://github.com/Windows81/Obj-to-Roblox-Mesh
cd Obj-to-Roblox-Mesh
git submodule update --init --recursive
msbuild /p:Configuration=Release
```

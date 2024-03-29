xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 34;
 0.00000;137.37331;-208.61367;,
 167.72207;137.37331;-127.84287;,
 167.72207;-138.32508;-127.84287;,
 0.00000;-138.32508;-208.61367;,
 209.14590;137.37331;53.64713;,
 209.14590;-138.32508;53.64713;,
 93.07868;137.37331;199.19085;,
 93.07868;-138.32508;199.19085;,
 -93.07877;137.37331;199.19082;,
 -93.07877;-138.32508;199.19082;,
 -209.14590;137.37331;53.64703;,
 -209.14590;-138.32508;53.64703;,
 -167.72198;137.37331;-127.84297;,
 -167.72198;-138.32508;-127.84297;,
 0.00000;137.37331;-208.61367;,
 0.00000;-138.32508;-208.61367;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;137.37331;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 0.00000;-138.32508;5.91090;,
 -152.32497;140.45720;158.23587;,
 152.32500;140.45720;158.23587;,
 152.32500;140.45720;-146.41414;,
 -152.32497;140.45720;-146.41414;;
 
 22;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 3;16,1,0;,
 3;17,4,1;,
 3;18,6,4;,
 3;19,8,6;,
 3;20,10,8;,
 3;21,12,10;,
 3;22,14,12;,
 3;23,3,2;,
 3;24,2,5;,
 3;25,5,7;,
 3;26,7,9;,
 3;27,9,11;,
 3;28,11,13;,
 3;29,13,15;,
 4;30,31,32,33;;
 
 MeshMaterialList {
  2;
  22;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1;;
  Material {
   0.800000;0.796863;0.018824;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.009412;0.800000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\�ؑ�����\\Documents\\Visual Studio 2015\\Projects\\3DACTION\\3DModel\\DATA\\TEX\\mahoujin1.png";
   }
  }
 }
 MeshNormals {
  10;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.781832;0.000000;-0.623489;,
  0.974928;0.000000;0.222521;,
  0.433884;0.000000;0.900969;,
  -0.433884;0.000000;0.900969;,
  -0.974928;0.000000;0.222521;,
  -0.781832;0.000000;-0.623490;,
  0.000000;-1.000000;-0.000000;,
  0.000000;1.000000;0.000000;;
  22;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,1,1,7;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  4;9,9,9,9;;
 }
 MeshTextureCoords {
  34;
  0.000000;0.000000;,
  0.142857;0.000000;,
  0.142857;1.000000;,
  0.000000;1.000000;,
  0.285714;0.000000;,
  0.285714;1.000000;,
  0.428571;0.000000;,
  0.428571;1.000000;,
  0.571429;0.000000;,
  0.571429;1.000000;,
  0.714286;0.000000;,
  0.714286;1.000000;,
  0.857143;0.000000;,
  0.857143;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.071429;0.000000;,
  0.214286;0.000000;,
  0.357143;0.000000;,
  0.500000;0.000000;,
  0.642857;0.000000;,
  0.785714;0.000000;,
  0.928571;0.000000;,
  0.071429;1.000000;,
  0.214286;1.000000;,
  0.357143;1.000000;,
  0.500000;1.000000;,
  0.642857;1.000000;,
  0.785714;1.000000;,
  0.928571;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}

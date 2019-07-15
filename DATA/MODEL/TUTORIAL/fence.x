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
 160;
 -485.53946;158.11846;333.76211;,
 -449.87950;158.11846;333.76211;,
 -449.87950;51.32655;333.76211;,
 -485.53946;51.32655;333.76211;,
 -449.87950;158.11846;333.76211;,
 -449.87950;158.11846;370.21211;,
 -449.87950;51.32655;370.21211;,
 -449.87950;51.32655;333.76211;,
 -449.87950;158.11846;370.21211;,
 -485.53946;158.11846;370.21211;,
 -485.53946;51.32655;370.21211;,
 -449.87950;51.32655;370.21211;,
 -485.53946;158.11846;370.21211;,
 -485.53946;158.11846;333.76211;,
 -485.53946;51.32655;333.76211;,
 -485.53946;51.32655;370.21211;,
 -449.87950;158.11846;333.76211;,
 -485.53946;158.11846;333.76211;,
 -485.53946;51.32655;333.76211;,
 -449.87950;51.32655;333.76211;,
 -485.53946;158.11846;153.11554;,
 -449.87950;158.11846;153.11554;,
 -449.87950;51.32655;153.11554;,
 -485.53946;51.32655;153.11554;,
 -449.87950;158.11846;153.11554;,
 -449.87950;158.11846;189.56553;,
 -449.87950;51.32655;189.56553;,
 -449.87950;51.32655;153.11554;,
 -449.87950;158.11846;189.56553;,
 -485.53946;158.11846;189.56553;,
 -485.53946;51.32655;189.56553;,
 -449.87950;51.32655;189.56553;,
 -485.53946;158.11846;189.56553;,
 -485.53946;158.11846;153.11554;,
 -485.53946;51.32655;153.11554;,
 -485.53946;51.32655;189.56553;,
 -449.87950;158.11846;153.11554;,
 -485.53946;158.11846;153.11554;,
 -485.53946;51.32655;153.11554;,
 -449.87950;51.32655;153.11554;,
 -485.53946;158.11846;153.11554;,
 -449.87950;158.11846;153.11554;,
 -449.87950;51.32655;153.11554;,
 -485.53946;51.32655;153.11554;,
 -449.87950;158.11846;153.11554;,
 -449.87950;158.11846;189.56553;,
 -449.87950;51.32655;189.56553;,
 -449.87950;51.32655;153.11554;,
 -449.87950;158.11846;189.56553;,
 -485.53946;158.11846;189.56553;,
 -485.53946;51.32655;189.56553;,
 -449.87950;51.32655;189.56553;,
 -485.53946;158.11846;189.56553;,
 -485.53946;158.11846;153.11554;,
 -485.53946;51.32655;153.11554;,
 -485.53946;51.32655;189.56553;,
 -449.87950;158.11846;153.11554;,
 -485.53946;158.11846;153.11554;,
 -485.53946;51.32655;153.11554;,
 -449.87950;51.32655;153.11554;,
 -485.53946;158.11846;-345.14742;,
 -449.87950;158.11846;-345.14742;,
 -449.87950;51.32655;-345.14742;,
 -485.53946;51.32655;-345.14742;,
 -449.87950;158.11846;-345.14742;,
 -449.87950;158.11846;-308.69742;,
 -449.87950;51.32655;-308.69742;,
 -449.87950;51.32655;-345.14742;,
 -449.87950;158.11846;-308.69742;,
 -485.53946;158.11846;-308.69742;,
 -485.53946;51.32655;-308.69742;,
 -449.87950;51.32655;-308.69742;,
 -485.53946;158.11846;-308.69742;,
 -485.53946;158.11846;-345.14742;,
 -485.53946;51.32655;-345.14742;,
 -485.53946;51.32655;-308.69742;,
 -449.87950;158.11846;-345.14742;,
 -485.53946;158.11846;-345.14742;,
 -485.53946;51.32655;-345.14742;,
 -449.87950;51.32655;-345.14742;,
 -485.53946;158.11846;-170.97981;,
 -449.87950;158.11846;-170.97981;,
 -449.87950;51.32655;-170.97981;,
 -485.53946;51.32655;-170.97981;,
 -449.87950;158.11846;-170.97981;,
 -449.87950;158.11846;-134.52981;,
 -449.87950;51.32655;-134.52981;,
 -449.87950;51.32655;-170.97981;,
 -449.87950;158.11846;-134.52981;,
 -485.53946;158.11846;-134.52981;,
 -485.53946;51.32655;-134.52981;,
 -449.87950;51.32655;-134.52981;,
 -485.53946;158.11846;-134.52981;,
 -485.53946;158.11846;-170.97981;,
 -485.53946;51.32655;-170.97981;,
 -485.53946;51.32655;-134.52981;,
 -449.87950;158.11846;-170.97981;,
 -485.53946;158.11846;-170.97981;,
 -485.53946;51.32655;-170.97981;,
 -449.87950;51.32655;-170.97981;,
 -485.53946;158.11846;-13.05663;,
 -449.87950;158.11846;-13.05663;,
 -449.87950;51.32655;-13.05663;,
 -485.53946;51.32655;-13.05663;,
 -449.87950;158.11846;-13.05663;,
 -449.87950;158.11846;23.39337;,
 -449.87950;51.32655;23.39337;,
 -449.87950;51.32655;-13.05663;,
 -449.87950;158.11846;23.39337;,
 -485.53946;158.11846;23.39337;,
 -485.53946;51.32655;23.39337;,
 -449.87950;51.32655;23.39337;,
 -485.53946;158.11846;23.39337;,
 -485.53946;158.11846;-13.05663;,
 -485.53946;51.32655;-13.05663;,
 -485.53946;51.32655;23.39337;,
 -449.87950;158.11846;-13.05663;,
 -485.53946;158.11846;-13.05663;,
 -485.53946;51.32655;-13.05663;,
 -449.87950;51.32655;-13.05663;,
 -485.53946;108.49668;-339.66985;,
 -449.87950;108.49668;-339.66985;,
 -449.87950;108.49675;350.00628;,
 -485.53946;108.49675;350.00628;,
 -449.87950;108.49668;-339.66985;,
 -449.87950;120.24567;-339.66959;,
 -449.87950;120.24575;350.00618;,
 -449.87950;108.49675;350.00628;,
 -449.87950;120.24567;-339.66959;,
 -485.53946;120.24567;-339.66959;,
 -485.53946;120.24575;350.00618;,
 -449.87950;120.24575;350.00618;,
 -485.53946;120.24567;-339.66959;,
 -485.53946;108.49668;-339.66985;,
 -485.53946;108.49675;350.00628;,
 -485.53946;120.24575;350.00618;,
 -449.87950;108.49668;-339.66985;,
 -485.53946;108.49668;-339.66985;,
 -485.53946;108.49675;350.00628;,
 -449.87950;108.49675;350.00628;,
 -485.53946;145.37654;-339.66985;,
 -449.87950;145.37654;-339.66985;,
 -449.87950;145.37654;350.00628;,
 -485.53946;145.37654;350.00628;,
 -449.87950;145.37654;-339.66985;,
 -449.87950;157.12549;-339.66959;,
 -449.87950;157.12559;350.00618;,
 -449.87950;145.37654;350.00628;,
 -449.87950;157.12549;-339.66959;,
 -485.53946;157.12549;-339.66959;,
 -485.53946;157.12559;350.00618;,
 -449.87950;157.12559;350.00618;,
 -485.53946;157.12549;-339.66959;,
 -485.53946;145.37654;-339.66985;,
 -485.53946;145.37654;350.00628;,
 -485.53946;157.12559;350.00618;,
 -449.87950;145.37654;-339.66985;,
 -485.53946;145.37654;-339.66985;,
 -485.53946;145.37654;350.00628;,
 -449.87950;145.37654;350.00628;;
 
 48;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;12,5,16,17;,
 4;18,19,6,15;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;28,29,30,31;,
 4;32,33,34,35;,
 4;32,25,36,37;,
 4;38,39,26,35;,
 4;40,41,42,43;,
 4;44,45,46,47;,
 4;48,49,50,51;,
 4;52,53,54,55;,
 4;52,45,56,57;,
 4;58,59,46,55;,
 4;60,61,62,63;,
 4;64,65,66,67;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;72,65,76,77;,
 4;78,79,66,75;,
 4;80,81,82,83;,
 4;84,85,86,87;,
 4;88,89,90,91;,
 4;92,93,94,95;,
 4;92,85,96,97;,
 4;98,99,86,95;,
 4;100,101,102,103;,
 4;104,105,106,107;,
 4;108,109,110,111;,
 4;112,113,114,115;,
 4;112,105,116,117;,
 4;118,119,106,115;,
 4;120,121,122,123;,
 4;124,125,126,127;,
 4;128,129,130,131;,
 4;132,133,134,135;,
 4;132,125,136,137;,
 4;138,139,126,135;,
 4;140,141,142,143;,
 4;144,145,146,147;,
 4;148,149,150,151;,
 4;152,153,154,155;,
 4;152,145,156,157;,
 4;158,159,146,155;;
 
 MeshMaterialList {
  2;
  48;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\�ؑ�����\\Documents\\Visual Studio 2015\\Projects\\3DACTION\\3D_ACTION_MASTER\\DATA\\TEX\\thCAHN3LSM.jpg";
   }
  }
  Material {
   0.216471;0.602353;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  48;
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000023;-1.000000;,
  0.000000;0.000008;1.000000;,
  0.000000;-1.000000;-0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000023;-1.000000;,
  0.000000;0.000008;1.000000;;
  48;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;,
  4;11,11,11,11;,
  4;12,12,12,12;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,16,16,16;,
  4;17,17,17,17;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;22,22,22,22;,
  4;23,23,23,23;,
  4;24,24,24,24;,
  4;25,25,25,25;,
  4;26,26,26,26;,
  4;27,27,27,27;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;30,30,30,30;,
  4;31,31,31,31;,
  4;32,32,32,32;,
  4;33,33,33,33;,
  4;34,34,34,34;,
  4;35,35,35,35;,
  4;36,36,36,36;,
  4;37,37,37,37;,
  4;38,38,38,38;,
  4;39,39,39,39;,
  4;40,40,40,40;,
  4;41,41,41,41;,
  4;42,42,42,42;,
  4;43,43,43,43;,
  4;44,44,44,44;,
  4;45,45,45,45;,
  4;46,46,46,46;,
  4;47,47,47,47;;
 }
 MeshTextureCoords {
  160;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;;
 }
}

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
 148;
 -130.51193;174.78250;-6.40526;,
 -124.88173;174.78250;-4.07310;,
 -124.88173;-2.22532;-4.07310;,
 -130.51193;-2.22532;-6.40526;,
 -122.54962;174.78250;1.55723;,
 -122.54962;-2.22532;1.55723;,
 -124.88173;174.78250;7.18756;,
 -124.88173;-2.22532;7.18756;,
 -130.51193;174.78250;9.51972;,
 -130.51193;-2.22532;9.51972;,
 -136.14238;174.78250;7.18756;,
 -136.14238;-2.22532;7.18756;,
 -138.47444;174.78250;1.55723;,
 -138.47444;-2.22532;1.55723;,
 -136.14238;174.78250;-4.07310;,
 -136.14238;-2.22532;-4.07310;,
 -130.51193;174.78250;-6.40526;,
 -130.51193;-2.22532;-6.40526;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;174.78250;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 -130.51193;-2.22532;1.55723;,
 134.04492;174.78250;-6.40526;,
 139.67514;174.78250;-4.07310;,
 139.67514;-3.73469;-4.07310;,
 134.04492;-3.73469;-6.40526;,
 142.00740;174.78250;1.55723;,
 142.00740;-3.73469;1.55723;,
 139.67514;174.78250;7.18756;,
 139.67514;-3.73469;7.18756;,
 134.04492;174.78250;9.51972;,
 134.04492;-3.73469;9.51972;,
 128.41461;174.78250;7.18756;,
 128.41461;-3.73469;7.18756;,
 126.08244;174.78250;1.55723;,
 126.08244;-3.73469;1.55723;,
 128.41461;174.78250;-4.07310;,
 128.41461;-3.73469;-4.07310;,
 134.04492;174.78250;-6.40526;,
 134.04492;-3.73469;-6.40526;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;174.78250;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 134.04492;-3.73469;1.55723;,
 -130.22191;172.09680;-1.67231;,
 132.16898;172.09680;-1.67231;,
 132.16898;43.60199;-1.67231;,
 -130.22191;43.60199;-1.67231;,
 132.16898;172.09680;-1.67231;,
 132.16898;172.09680;4.78677;,
 132.16898;43.60199;4.78677;,
 132.16898;43.60199;-1.67231;,
 132.16898;172.09680;4.78677;,
 -130.22191;172.09680;4.78677;,
 -130.22191;43.60199;4.78677;,
 132.16898;43.60199;4.78677;,
 -130.22191;172.09680;4.78677;,
 -130.22191;172.09680;-1.67231;,
 -130.22191;43.60199;-1.67231;,
 -130.22191;43.60199;4.78677;,
 132.16898;172.09680;-1.67231;,
 -130.22191;172.09680;-1.67231;,
 -130.22191;43.60199;-1.67231;,
 132.16898;43.60199;-1.67231;,
 -122.53452;170.20894;-1.91799;,
 124.48152;170.20894;-1.91799;,
 124.48152;45.48975;-2.23692;,
 -122.53452;45.48975;-2.23692;,
 -129.74154;175.62744;-13.86488;,
 -129.74154;199.68199;-1.81907;,
 -121.22390;175.62744;-10.33674;,
 -129.74154;199.68199;-1.81907;,
 -117.69574;175.62744;-1.81907;,
 -129.74154;199.68199;-1.81907;,
 -121.22390;175.62744;6.69860;,
 -129.74154;199.68199;-1.81907;,
 -129.74154;175.62744;10.22674;,
 -129.74154;199.68199;-1.81907;,
 -138.25922;175.62744;6.69860;,
 -129.74154;199.68199;-1.81907;,
 -141.78734;175.62744;-1.81907;,
 -129.74154;199.68199;-1.81907;,
 -138.25922;175.62744;-10.33674;,
 -129.74154;199.68199;-1.81907;,
 -129.74154;175.62744;-13.86488;,
 -129.74154;175.62744;-1.81907;,
 -129.74154;175.62744;-13.86488;,
 -121.22390;175.62744;-10.33674;,
 -117.69574;175.62744;-1.81907;,
 -121.22390;175.62744;6.69860;,
 -129.74154;175.62744;10.22674;,
 -138.25922;175.62744;6.69860;,
 -141.78734;175.62744;-1.81907;,
 -138.25922;175.62744;-10.33674;,
 134.93913;175.62744;-13.86488;,
 134.93913;199.68199;-1.81907;,
 143.45681;175.62744;-10.33674;,
 134.93913;199.68199;-1.81907;,
 146.98493;175.62744;-1.81907;,
 134.93913;199.68199;-1.81907;,
 143.45681;175.62744;6.69860;,
 134.93913;199.68199;-1.81907;,
 134.93913;175.62744;10.22674;,
 134.93913;199.68199;-1.81907;,
 126.42152;175.62744;6.69860;,
 134.93913;199.68199;-1.81907;,
 122.89332;175.62744;-1.81907;,
 134.93913;199.68199;-1.81907;,
 126.42152;175.62744;-10.33674;,
 134.93913;199.68199;-1.81907;,
 134.93913;175.62744;-13.86488;,
 134.93913;175.62744;-1.81907;,
 134.93913;175.62744;-13.86488;,
 143.45681;175.62744;-10.33674;,
 146.98493;175.62744;-1.81907;,
 143.45681;175.62744;6.69860;,
 134.93913;175.62744;10.22674;,
 126.42152;175.62744;6.69860;,
 122.89332;175.62744;-1.81907;,
 126.42152;175.62744;-10.33674;,
 -116.13411;165.13094;-7.15708;,
 121.22578;165.13094;-7.15708;,
 121.22578;50.76267;-4.04525;,
 -116.13411;50.76267;-4.04525;;
 
 88;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 4;34,35,36,37;,
 4;35,38,39,36;,
 4;38,40,41,39;,
 4;40,42,43,41;,
 4;42,44,45,43;,
 4;44,46,47,45;,
 4;46,48,49,47;,
 4;48,50,51,49;,
 3;52,35,34;,
 3;53,38,35;,
 3;54,40,38;,
 3;55,42,40;,
 3;56,44,42;,
 3;57,46,44;,
 3;58,48,46;,
 3;59,50,48;,
 3;60,37,36;,
 3;61,36,39;,
 3;62,39,41;,
 3;63,41,43;,
 3;64,43,45;,
 3;65,45,47;,
 3;66,47,49;,
 3;67,49,51;,
 4;68,69,70,71;,
 4;72,73,74,75;,
 4;76,77,78,79;,
 4;80,81,82,83;,
 4;80,73,84,85;,
 4;86,87,74,83;,
 4;88,89,90,91;,
 3;92,93,94;,
 3;94,95,96;,
 3;96,97,98;,
 3;98,99,100;,
 3;100,101,102;,
 3;102,103,104;,
 3;104,105,106;,
 3;106,107,108;,
 3;109,110,111;,
 3;109,111,112;,
 3;109,112,113;,
 3;109,113,114;,
 3;109,114,115;,
 3;109,115,116;,
 3;109,116,117;,
 3;109,117,110;,
 3;118,119,120;,
 3;120,121,122;,
 3;122,123,124;,
 3;124,125,126;,
 3;126,127,128;,
 3;128,129,130;,
 3;130,131,132;,
 3;132,133,134;,
 3;135,136,137;,
 3;135,137,138;,
 3;135,138,139;,
 3;135,139,140;,
 3;135,140,141;,
 3;135,141,142;,
 3;135,142,143;,
 3;135,143,136;,
 4;144,145,146,147;;
 
 MeshMaterialList {
  2;
  88;
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
  0,
  0,
  0,
  1;;
  Material {
   0.062745;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "DATA\\TEX\\tuto3.png";
   }
  }
 }
 MeshNormals {
  41;
  0.000000;1.000000;0.000000;,
  0.000008;0.000000;-1.000000;,
  0.707113;0.000000;-0.707101;,
  1.000000;0.000000;-0.000000;,
  0.707112;0.000000;0.707101;,
  0.000008;0.000000;1.000000;,
  -0.707109;0.000000;0.707104;,
  -1.000000;0.000000;-0.000000;,
  -0.707110;0.000000;-0.707104;,
  0.000000;-1.000000;-0.000000;,
  0.000003;0.000000;-1.000000;,
  0.707104;0.000000;-0.707110;,
  1.000000;0.000000;-0.000000;,
  0.707104;0.000000;0.707110;,
  0.000003;0.000000;1.000000;,
  -0.707106;0.000000;0.707107;,
  -1.000000;0.000000;-0.000000;,
  -0.707106;0.000000;-0.707107;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.002557;-0.999997;,
  0.000000;0.447765;-0.894151;,
  0.632261;0.447764;-0.632261;,
  0.894151;0.447765;0.000000;,
  0.632261;0.447764;0.632261;,
  0.000001;0.447765;0.894151;,
  -0.632261;0.447765;0.632260;,
  -0.894151;0.447765;-0.000000;,
  -0.632261;0.447765;-0.632260;,
  0.000000;-1.000000;-0.000000;,
  -0.000002;0.447765;-0.894151;,
  0.632261;0.447765;-0.632260;,
  0.894152;0.447765;0.000000;,
  0.632261;0.447765;0.632260;,
  -0.000002;0.447765;0.894151;,
  -0.632260;0.447763;0.632262;,
  -0.894152;0.447765;-0.000000;,
  -0.632260;0.447763;-0.632262;,
  0.000000;-0.027199;-0.999630;;
  88;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,11,11,10;,
  4;11,12,12,11;,
  4;12,13,13,12;,
  4;13,14,14,13;,
  4;14,15,15,14;,
  4;15,16,16,15;,
  4;16,17,17,16;,
  4;17,10,10,17;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;18,18,18,18;,
  4;19,19,19,19;,
  4;20,20,20,20;,
  4;21,21,21,21;,
  4;0,0,0,0;,
  4;9,9,9,9;,
  4;22,22,22,22;,
  3;23,24,24;,
  3;24,24,25;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,30,30;,
  3;30,30,23;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;32,33,33;,
  3;33,33,34;,
  3;34,35,35;,
  3;35,35,36;,
  3;36,37,37;,
  3;37,37,38;,
  3;38,39,39;,
  3;39,39,32;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  3;31,31,31;,
  4;40,40,40,40;;
 }
 MeshTextureCoords {
  148;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
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
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;;
 }
}
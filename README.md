# Mini raytracing in C
### Notion (KR)
https://u-lo-l.notion.site/MiniRT-d1d62b4890274dddb36b79dec2c259d3

### Implementation

- Phong reflection model (ambient, diffuse, specular)
- object : plane, quadrics( sphere, cylinder, ellipsoid, .... )
- light source : spot light
- keyboard, mouse input event
- camera move, rotation.
- object translation, rotation, scaling
- image mapping
- nomal map
- Color disruption : checkerboard
- mirror reflection
- bounding sphere
- multi threading : 4

### Sample images
Works on Mac(intel)
```
cd bonus
make
./miniRT RT_files/[~]/[~.rt]
```
  <img src="./images/1.png" width="45%"></img>
  <img src="./images/2.png" width="45%"></img>
  <img src="./images/3.png" width="45%"></img>
  <img src="./images/4.png" width="45%"></img>
  <img src="./images/5.png" width="45%"></img>
  <img src="./images/6.png" width="45%"></img>

### Demo (x4 faster)
<img src="https://user-images.githubusercontent.com/60467872/216758398-1de48069-85a5-4042-b378-966aba4a3cc7.gif" width="600px"></img>
<img src="https://user-images.githubusercontent.com/60467872/217010216-5d5e8008-e05f-49ec-a79f-797697b31e64.gif" width="600px"></img>
<img src="https://user-images.githubusercontent.com/60467872/217010602-b5e088e6-d9e1-4205-94b2-c2cae5b8e5a4.gif" width="600px"></img>

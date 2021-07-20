struct Result {
    float avg[3];
};

/*
This is the function you need to implement. Quick reference:
- x coordinates: 0 <= x < nx
- y coordinates: 0 <= y < ny
- horizontal position: 0 <= x0 < x1 <= nx
- vertical position: 0 <= y0 < y1 <= ny
- color components: 0 <= c < 3
- input: data[c + 3 * x + 3 * nx * y]
- output: avg[c]
*/
Result calculate(int ny, int nx, const float *data, int y0, int x0, int y1, int x1) {
  double s0=0, s1=0, s2=0;
  double c = (x1 - x0) * (y1 - y0);
  
  Result result{{0.0f, 0.0f, 0.0f}};
  for(int x=x0; x<x1; x++){
    for(int y=y0; y<y1; y++){
      s0 += data[3 * x + 3 * nx * y];
      s1 += data[1 + 3 * x + 3 * nx * y];
      s2 += data[2 + 3 * x + 3 * nx * y];
    }
  }
  result.avg[0] = s0 / c;
  result.avg[1] = s1 / c;
  result.avg[2] = s2 / c;
  return result;
}

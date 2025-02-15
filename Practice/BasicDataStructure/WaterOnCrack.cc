
#include <iostream>
#include <vector>

bool Cal_WaterPond(std::vector<char> &data, int& result) {

  // 한 번에 한 줄만 채운다.
  bool calc_on = false;
  int begin_pos = 0;
  int end_pos = -1;
  int width = 0;

  for(int i = 0; i < data.size(); i++){
      if(data[i] == '\\'){
        // 하강
        calc_on == true;
        begin_pos = i;
        width = 1; 
      }
      else if(calc_on == true && data[i] == '/'){
        // 상승, 종료 
        end_pos = i;
        width++;
        break;
      }
      else {
        // 횡보
        width++;
      }
  }
  
  // recurse, do it again
  if(end_pos == -1) {
    // escape
    return true;
  }
  else {
     // calculate the pond
    result += (width - 1);

    // fill the pond
    data[begin_pos] = '_';
    data[end_pos] = '_';
    // recurse
    return Cal_WaterPond(data, result);
  }
}

int main() {  //
  char temp;
  std::vector<char> data;

  while(true){
    std::cin >> temp;
    if(temp == '\n'){
      break;
    }
    else{
      data.push_back(temp);
    }
  }

  int result = 0; 
  Cal_WaterPond(data, result);

  
}
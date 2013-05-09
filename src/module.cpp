#include "ocv.hpp"

extern "C" {

 void InitAll(v8::Handle<v8::Object> exports) {
  v8::HandleScope scope;
  Ocv::Init(exports);
 }

NODE_MODULE(ocv, InitAll)

}
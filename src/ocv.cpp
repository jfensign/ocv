#include "ocv.hpp"

extern "C" {

Ocv::Ocv() {}
Ocv::~Ocv() {}

void 
Ocv::Init(v8::Handle<v8::Object> target) {
 v8::HandleScope scope;

 char out [21];
 int n = sprintf(out, "%i.%i", CV_MAJOR_VERSION, CV_MINOR_VERSION);
 target->Set(v8::String::NewSymbol("version"), v8::String::New(out, n));
 NODE_SET_METHOD(target, "readImage", ReadImage);
}

v8::Handle<v8::Value>
Ocv::ReadImage(const v8::Arguments &args) {
 v8::HandleScope scope;

 if(!args[0]->IsString()) {
  return v8::ThrowException(v8::Exception::TypeError(
   v8::String::New("Invalid filename.")
  ));
 }
 if (!args[1]->IsFunction()) {
  return v8::ThrowException(v8::Exception::TypeError(
   v8::String::New("Second argument must be a callback function.")
  ));
 }

 v8::Local<v8::Function> callback = v8::Local<v8::Function>::Cast(args[1]);
 std::string f_name = std::string(*v8::String::AsciiValue(args[0]->ToString()));
 cv::Mat mat(cv::imread(f_name));
 
 v8::TryCatch try_catch;

 if (try_catch.HasCaught()) {
  v8::Handle<v8::Value> exception = try_catch.Exception();
  v8::ThrowException(exception);
 }
 
 const unsigned argc = 3;
 v8::Local<v8::Value> argv[argc] = {
  v8::Local<v8::Value>::New(v8::Null()),
  args[0],
  v8::Local<v8::Value>::New(v8::Integer::New(42))
 };

 callback->Call(v8::Context::GetCurrent()->Global(), argc, argv);
 
 if (try_catch.HasCaught()) {
  v8::Handle<v8::Value> exception = try_catch.Exception();
  v8::ThrowException(exception);
 }

 return v8::Undefined();
}

}

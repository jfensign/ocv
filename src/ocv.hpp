#ifndef OCV_HPP
#define OCV_HPP

#include <v8.h>
#include <node.h>
#include <stdio.h>
#include <string.h>

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui_c.h"

class Ocv : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object> target);
    static v8::Handle<v8::Value> ReadImage(const v8::Arguments&);

  protected:
  	 Ocv();
  	~Ocv();
  	static std::string filename;
};

#endif




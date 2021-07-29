#include <napi.h>
#include <QtGui/QIcon/qicon_wrap.h>
#include <QtGui/QFont/qfont_wrap.h>

#include "FontIcon.h"


Napi::Value CreateIcon(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  Napi::Object fontObject = info[0].As<Napi::Object>();
  QFontWrap* fontWrap = Napi::ObjectWrap<QFontWrap>::Unwrap(fontObject);
  QFont* fontArg = fontWrap->getInternalInstance();
  QFont font = *fontArg;
  std::string text = info[1].As<Napi::String>().Utf8Value();

  qreal scale = info[2].As<Napi::Number>().DoubleValue();

  QRgb normalOnRgb = info[3].As<Napi::Number>().Uint32Value();
  QRgb disabledOnRgb = info[4].As<Napi::Number>().Uint32Value();
  QRgb activeOnRgb = info[5].As<Napi::Number>().Uint32Value();
  QRgb selectedOnRgb = info[6].As<Napi::Number>().Uint32Value();
  QRgb normalOffRgb = info[7].As<Napi::Number>().Uint32Value();
  QRgb disabledOffRgb = info[8].As<Napi::Number>().Uint32Value();
  QRgb activeOffRgb = info[9].As<Napi::Number>().Uint32Value();
  QRgb selectedOffRgb = info[10].As<Napi::Number>().Uint32Value();

  QIcon* icon = FontIconEngine::createIcon(font, QString::fromStdString(text), scale, normalOnRgb, disabledOnRgb, activeOnRgb,
                                           selectedOnRgb, normalOffRgb, disabledOffRgb, activeOffRgb, selectedOffRgb);
  auto instance = QIconWrap::constructor.New({Napi::External<QIcon>::New(env, icon)});
  return instance;
}

Napi::Object Main(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "FontIconCreateIcon"), Napi::Function::New<CreateIcon>(env));
  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Main)

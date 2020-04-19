#include "builder.h"

namespace pip {

PipelineBuilder::PipelineBuilder() {
  inputs = new std::vector<IInputProcessor *>();
  outputs = new std::vector<IOutputProcessor *>();
}

PipelineBuilder::~PipelineBuilder() {
  if (inputs != nullptr) {
    delete inputs;
  }
  if (outputs != nullptr) {
    delete outputs;
  }
  if (converter != nullptr) {
    delete converter;
  }
}

std::unique_ptr<Pipeline> PipelineBuilder::build() {
  auto pipe = std::make_unique<Pipeline>(inputs, converter, outputs);
  inputs = nullptr;
  outputs = nullptr;
  converter = nullptr;
  return pipe;
}

PipelineBuilder &PipelineBuilder::add_input_processor(IInputProcessor *in) {
  inputs->push_back(in);
  return *this;
}

PipelineBuilder &PipelineBuilder::add_output_processor(IOutputProcessor *out) {
  outputs->push_back(out);
  return *this;
}

PipelineBuilder &PipelineBuilder::set_converter(IConverter *conv) {
  if (converter != nullptr) {
    return *this;
  }

  converter = conv;
  return *this;
}

} // namespace pip
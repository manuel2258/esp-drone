#include "pipeline.h"

namespace pip {

Pipeline::Pipeline(std::vector<IInputProcessor *> *in, IConverter *conv,
                   std::vector<IOutputProcessor *> *out)
    : inputs(in), converter(conv), outputs(out) {}

Pipeline::~Pipeline() {
  delete converter;

  for (auto input : *inputs) {
    delete input;
  }
  delete inputs;

  for (auto output : *outputs) {
    delete output;
  }
  delete outputs;
}

std::unique_ptr<Output> Pipeline::process_input(pkg::InputPkg &pkg) {
  Input input(pkg);
  return std::unique_ptr<Output>(process(input));
}

Output *Pipeline::process(Input &in) {
  for (auto input = inputs->begin();
       input != inputs->end() && !(*input)->process(in); ++input) {
  }

  auto out = new Output();
  converter->convert(in, *out);

  for (auto output = outputs->begin();
       output != outputs->end() && !(*output)->process(*out); ++output) {
  }

  return out;
}

std::unique_ptr<Pipeline> PipelineBuilder::build() {
  return std::make_unique<Pipeline>(inputs, converter, outputs);
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
  if (converter != nullptr)
    return;

  converter = conv;
  return *this;
}

} // namespace pip
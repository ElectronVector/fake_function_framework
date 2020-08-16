require 'stringio'
require 'fff_mock_generator.rb'

# Test the contents of the .c file created for the mock.
describe "FffMockGenerator.create_mock_source" do

  context "when there is nothing to mock," do
    let(:mock_source) {
      parsed_header = {}
      FffMockGenerator.create_mock_source("mock_my_module", parsed_header)
    }
    it "then the generated file includes the fff header" do
      expect(mock_source).to include(
        # fff.h also requires including string.h
        %{#include <string.h>\n} +
        %{#include "fff.h"}
      )
    end
    it "then the generated file includes the mock header" do
      expect(mock_source).to include(
        %{#include "mock_my_module.h"\n}
      )
    end
    it "then the generated file defines the init function" do
      expect(mock_source).to include(
        "void mock_my_module_Init(void)\n" +
        "{\n" +
        "    FFF_RESET_HISTORY();\n" +
        "}"
      )
    end
    it "then the generated file defines the verify function" do
      expect(mock_source).to include(
        "void mock_my_module_Verify(void)\n" +
        "{\n" +
        "}"
      )
    end
    it "then the generated file defines the destroy function" do
      expect(mock_source).to include(
        "void mock_my_module_Destroy(void)\n" +
        "{\n" +
        "}"
      )
    end
  end

  context "when there are multiple functions," do
    let(:mock_source) {
      parsed_header = parse_header("display", %q(
        int a_function(char * str);
        void another_function();
        bool three (float a, int b);
      ))
      FffMockGenerator.create_mock_source("mock_display", parsed_header)
    }
    it "then the generated file contains the first fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VALUE_FUNC1(int, a_function, char*)"
      )
    end
    it "then the generated file contains the second fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VOID_FUNC0(another_function)"
      )
    end
    it "then the generated file contains the third fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VALUE_FUNC2(bool, three, float, int)"
      )
    end
    it "then the init function resets all of the fakes" do
      expect(mock_source).to include(
        "void mock_display_Init(void)\n" +
        "{\n" +
        "    FFF_RESET_HISTORY();\n" +
        "    RESET_FAKE(a_function)\n" +
        "    RESET_FAKE(another_function)\n" +
        "    RESET_FAKE(three)\n" +
        "}"
      )
    end
  end

  context "when there is a void function with variable arguments and " +
          "additional arguments" do
    let(:mock_source){
      parsed_header = parse_header("display",
        "void function_with_var_args(char * c, int value, ...)")
      FffMockGenerator.create_mock_source("mock_display", parsed_header)
    }
    it "then the generated file contains the vararg definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VOID_FUNC3_VARARG(function_with_var_args, char*, int, ...)"
      )
    end
  end

  context "when there are constant arguments" do
    it "works for a variable pointer to a const value and another pointer" do
      expect(parse_and_generate_header(
        "void a_function(const int * a, int * b)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC2(a_function, const int*, int*)"
      )
    end
  end

  context "when there are pre-includes" do
    let(:mock_source) {
      parsed_source = {}
      FffMockGenerator.create_mock_source("mock_display", parsed_source,
        [%{"another_header.h"}])
    }
    it "then they are included before the other files" do
      expect(mock_source).to include(
        %{#include "another_header.h"\n} +
        %{#include <string.h>}
      )
    end
  end

  context "when there are post-includes" do
    let(:mock_source) {
      parsed_source = {}
      FffMockGenerator.create_mock_source("mock_display", parsed_source,
        nil, [%{"another_header.h"}])
    }
    it "then they are included before the other files" do
      expect(mock_source).to include(
        %{#include "mock_display.h"\n} +
        %{#include "another_header.h"\n}
      )
    end
  end
end

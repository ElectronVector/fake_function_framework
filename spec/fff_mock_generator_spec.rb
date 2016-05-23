require 'stringio'
require 'fff_mock_generator.rb'

describe "FffMockGenerator.create_mock_header" do

  context "when there is nothing to mock," do
    let(:mock_header) {
      parsed_header = {}
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated header file starts with an opening include guard" do
      expect(mock_header).to start_with(
          "#ifndef mock_display_H\n" +
          "#define mock_display_H")
    end
    it "then the generated file ends with a closing include guard" do
      expect(mock_header).to end_with(
          "#endif // mock_display_H\n")
    end
    it "then the generated file includes the fff header" do
      expect(mock_header).to include(
          %{#include "fff.h"\n})
    end
    it "then the generated file has a prototype for the init function" do
      expect(mock_header).to include(
          "void mock_display_Init(void);")
    end
    it "then the generated file has a prototype for the verify function" do
      expect(mock_header).to include(
          "void mock_display_Verify(void);")
    end
    it "then the generated file has a prototype for the destroy function" do
      expect(mock_header).to include(
          "void mock_display_Destroy(void);")
    end
  end

  context "when there is a function with no args and a void return," do
      let(:mock_header) {
        parsed_header = create_cmock_style_parsed_header(
          [{:name => 'display_turnOffStatusLed', :return_type => 'void'}])
        FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
      }
      it "then the generated header file starts with an opening include guard" do
        expect(mock_header).to start_with(
          "#ifndef mock_display_H\n" +
          "#define mock_display_H")
      end
      it "then the generated header file contains a fake function declaration" do
        expect(mock_header).to include(
          "DECLARE_FAKE_VOID_FUNC0(display_turnOffStatusLed);"
        )
      end
      it "then the generated file ends with a closing include guard" do
          expect(mock_header).to end_with(
              "#endif // mock_display_H\n")
      end
  end

  context "when there is a function with no args and a bool return," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [{:name => 'display_isError', :return_type => 'bool'}])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC0(bool, display_isError);"
      )
    end
  end

  context "when there is a function with no args and an int return," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [{:name => 'display_isError', :return_type => 'int'}])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC0(int, display_isError);"
      )
    end
  end

  context "when there is a function with args and a void return," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [{:name => 'display_setVolume', :return_type => 'void', :args => ['int']}])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC1(display_setVolume, int);"
      )
    end
  end

  context "when there is a function with args and a value return," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [{:name => 'a_function', :return_type => 'int', :args => ['char *']}])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "FAKE_VALUE_FUNC1(int, a_function, char *);"
      )
    end
  end

  context "when there is a function with many args and a void return," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [{:name => 'a_function', :return_type => 'void',
          :args => ['int', 'char *', 'int', 'int', 'bool', 'applesauce']}])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC6(a_function, int, char *, int, int, bool, applesauce);"
      )
    end
  end

  context "when there are multiple functions," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        [ {:name => 'a_function', :return_type => 'int', :args => ['char *']},
          {:name => 'another_function', :return_type => 'void'},
          {:name => 'three', :return_type => 'bool', :args => ['float', 'int']}
        ])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the first fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC1(int, a_function, char *);"
      )
    end
    it "then the generated file contains the second fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC0(another_function);"
      )
    end
    it "then the generated file contains the third fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC2(bool, three, float, int);"
      )
    end
  end

  context "when there is a typedef," do
    let(:mock_header) {
      parsed_header = create_cmock_style_parsed_header(
        nil, ["typedef void (*displayCompleteCallback) (void);"])
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the typedef" do
      expect(mock_header).to include(
        "typedef void (*displayCompleteCallback) (void);"
      )
    end
  end

  context "when there is a void function with variable arguments" do
    let(:mock_header){
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "function_with_var_args",
        :return => {:type => "void"},
        :var_arg => "...",
        :args => [{:type => 'char *'}]
      }]
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC2_VARARG(function_with_var_args, char *, ...)"
      )
    end
  end

  context "when there is a function with a return value and variable arguments" do
    let(:mock_header){
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "function_with_var_args",
        :return => {:type => "int"},
        :var_arg => "...",
        :args => [{:type => 'char *'}]
      }]
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC2_VARARG(int, function_with_var_args, char *, ...)"
      )
    end
  end

  context "when there is a void function with variable arguments and " +
          "additional arguments" do
    let(:mock_header){
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "function_with_var_args",
        :return => {:type => "void"},
        :var_arg => "...",
        :args => [{:type => 'char *'}, {:type => 'int'}]
      }]
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC3_VARARG(function_with_var_args, char *, int, ...)"
      )
    end
  end

  context "when there is a function with a pointer to a const value" do
    let(:mock_header){
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "const_test_function",
        :return => {:type => "void"},
        :args => [{:type => "char *", :name => "a", :ptr? => false, :const? => true},
                  {:type => "char *", :name => "b", :ptr? => false, :const? => false}]
      }]
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the correct const argument in the declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC2(const_test_function, const char *, char *)"
      )
    end
  end

  context "when there are pre-includes" do
    let(:mock_header) {
      parsed_header = {}
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header,
        [%{"another_header.h"}])
    }
    it "then they are included before the other files" do
      expect(mock_header).to include(
        %{#include "another_header.h"\n} +
        %{#include "fff.h"}
      )
    end
  end

  context "when there are post-includes" do
    let(:mock_header) {
      parsed_header = {}
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header,
        nil, [%{"another_header.h"}])
    }
    it "then they are included after the other files" do
      expect(mock_header).to include(
        %{#include "display.h"\n} +
        %{#include "another_header.h"\n}
      )
    end
  end

end

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
      parsed_header = create_cmock_style_parsed_header(
        [ {:name => 'a_function', :return_type => 'int', :args => ['char *']},
          {:name => 'another_function', :return_type => 'void'},
          {:name => 'three', :return_type => 'bool', :args => ['float', 'int']}
        ])
      FffMockGenerator.create_mock_source("mock_display", parsed_header)
    }
    it "then the generated file contains the first fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VALUE_FUNC1(int, a_function, char *);"
      )
    end
    it "then the generated file contains the second fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VOID_FUNC0(another_function);"
      )
    end
    it "then the generated file contains the third fake function definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VALUE_FUNC2(bool, three, float, int);"
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
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "function_with_var_args",
        :return => {:type => "void"},
        :var_arg => "...",
        :args => [{:type => 'char *'}, {:type => 'int'}]
      }]
      FffMockGenerator.create_mock_source("mock_display", parsed_header)
    }
    it "then the generated file contains the vararg definition" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VOID_FUNC3_VARARG(function_with_var_args, char *, int, ...)"
      )
    end
  end

  context "when there is a function with a pointer to a const value" do
    let(:mock_source){
      parsed_header = {}
      parsed_header[:functions] = [{
        :name => "const_test_function",
        :return => {:type => "void"},
        :args => [{:type => "char *", :name => "a", :ptr? => false, :const? => true},
                  {:type => "char *", :name => "b", :ptr? => false, :const? => false}]
      }]
      FffMockGenerator.create_mock_source("mock_display", parsed_header)
    }
    it "then the generated file contains the correct const argument in the declaration" do
      expect(mock_source).to include(
        "DEFINE_FAKE_VOID_FUNC2(const_test_function, const char *, char *)"
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

# Create a CMock-style parsed header hash. This the type of hash created by
# CMock when parsing header files for automock generation. It contains all of
# includes, typedefs and functions (with return types and arguments) parsed from
# the header file.
def create_cmock_style_parsed_header(functions, typedefs = nil)
  parsed_header = {
      :includes => nil,
      :functions => [],
      :typedefs => []
  }

  # Add the typedefs.
  if typedefs
      typedefs.each do |typedef|
          parsed_header[:typedefs] << typedef
      end
  end

  # Add the functions.
  if functions
    functions.each do |function|
      # Build the array of arguments.
      args = []
      if function.key?(:args)
        function[:args].each do |arg|
          args << {
            :type => arg
          }
        end
      end
      parsed_header[:functions] << {
        :name => function[:name],
        :modifier => "",
        :return => {
          :type => function[:return_type],
          :name => "cmock_to_return",
          :ptr? => false,
          :const? => false,
          :str => "void cmock_to_return",
          :void? => true
        },
        :var_arg => nil,
        :args_string => "void",
        :args => args,
        :args_call => "",
        :contains_ptr? => false
      }
    end
  end
  parsed_header
end

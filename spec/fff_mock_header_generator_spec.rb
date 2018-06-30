require 'stringio'
require 'fff_mock_generator.rb'
require 'header_generator.rb'

# Test the contents of the .h file created for the mock.
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
        parsed_header = parse_header("display", "void display_turnOffStatusLed()")
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
      parsed_header = parse_header("display", "bool display_isError()")
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
      parsed_header = parse_header("display", "int display_isError()")
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
      parsed_header = parse_header("display", "void display_setVolume(int level)")
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
      parsed_header = parse_header("display", "int a_function(char * str)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC1(int, a_function, char*);"
      )
    end
  end

  context "when there is a function with many args and a void return," do
    let(:mock_header) {
      parsed_header = parse_header("display", "void a_function(int x, char * str, int y, int z, bool b, applesauce value)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC6(a_function, int, char*, int, int, bool, applesauce);"
      )
    end
  end

  context "when there are multiple functions," do
    let(:mock_header) {
      parsed_header = parse_header("display", %q(
        int a_function(char * str);
        void another_function();
        bool three (float a, int b);
      ))
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the first fake function declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC1(int, a_function, char*);"
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

  # This doesn't seem to work when I run it through the CMock parser. Is this
  # actually necessary?
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
      parsed_header = parse_header("display", "void function_with_var_args(char * fmt, ...)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC2_VARARG(function_with_var_args, char*, ...)"
      )
    end
  end

  context "when there is a function with a return value and variable arguments" do
    let(:mock_header){
      parsed_header = parse_header("display", "int function_with_var_args(char * fmt, ...)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC2_VARARG(int, function_with_var_args, char*, ...)"
      )
    end
  end

  context "when there is a void function with variable arguments and " +
          "additional arguments" do
    let(:mock_header){
      parsed_header = parse_header("display", "void function_with_var_args(char * fmt, int value, ...)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the vararg declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VOID_FUNC3_VARARG(function_with_var_args, char*, int, ...)"
      )
    end
  end

  context "when there are constant arguments" do
    it "works for a constant value" do
      expect(parse_and_generate_header(
        "void a_function(const int a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, const int)"
      )
    end

    it "works for a constant value with const reversed" do
      expect(parse_and_generate_header(
        "void a_function(int const a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, const int)"
      )
    end

    it "works for a variable pointer to a const value" do
      expect(parse_and_generate_header(
        "void a_function(const int * a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, const int*)"
      )
    end

    it "works for a variable pointer to a const value with alternate const placement" do
      expect(parse_and_generate_header(
        "void a_function(int const * a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, int const*)"
      )
    end

    it "works for a constant pointer to a variable value" do
      expect(parse_and_generate_header(
        "void a_function(int * const a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, int* const)"
      )
    end

    it "works for a constant pointer to a constant value" do
      expect(parse_and_generate_header(
        "void a_function(const int * const a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, const int* const)"
      )
    end

    it "works for a constant pointer to a constant value with alternate const placement" do
      expect(parse_and_generate_header(
        "void a_function(int const * const a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, int const* const)"
      )
    end

    it "works for a const char" do
      expect(parse_and_generate_header(
        "void a_function(const char a)"
      )).to include(
        "DECLARE_FAKE_VOID_FUNC1(a_function, const char)"
      )
    end

    it "works for a variable pointer to a const char" do
      expect(parse_and_generate_header(
        "void a_function(const char * a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, const char*)"
      )
    end

    it "works for a variable pointer to a const char with alternate const placement" do
      expect(parse_and_generate_header(
        "void a_function(char const * a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char const*)"
      )
    end

    it "works for a const pointer to a variable char" do
      expect(parse_and_generate_header(
        "void a_function(char * const a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char* const)"
      )
    end

    it "works for a const pointer to a const char" do
      expect(parse_and_generate_header(
        "void a_function(const char * const a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, const char* const)"
      )
    end

    it "works for a const pointer to a const char with alternate const placement" do
      expect(parse_and_generate_header(
        "void a_function(char const * const a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char const* const)"
      )
    end

    it "works for a variable double pointer to a const char" do
      expect(parse_and_generate_header(
        "void a_function(const char ** a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, const char**)"
      )
    end

    it "works for a variable double pointer to a const char with alternate const placement" do
      expect(parse_and_generate_header(
        "void a_function(char const ** a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char const**)"
      )
    end

    it "works for a const double pointer to a variable char" do
      expect(parse_and_generate_header(
        "void a_function(char ** const a)"
      )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char** const)"
      )
    end

      it "works for a const double pointer to a const char" do
        expect(parse_and_generate_header(
          "void a_function(const char ** const a)"
        )).to include(
            "DECLARE_FAKE_VOID_FUNC1(a_function, const char** const)"
        )
      end

      it "works for a const double pointer to a const char with alternate const placement" do
        expect(parse_and_generate_header(
          "void a_function(char const ** const a)"
        )).to include(
          "DECLARE_FAKE_VOID_FUNC1(a_function, char const** const)"
        )
      end

      it "fixes issue #11" do
        expect(parse_and_generate_header(
          "void Button_pollAll(Button * const *, size_t);"
        )).to include(
          "DECLARE_FAKE_VOID_FUNC2(Button_pollAll, Button* const*, size_t)"
        )
      end
  end

  context "when there are constant return values" do
    it "fixes issue #3" do
      expect(parse_and_generate_header(
        "char * const bar_return_const_ptr(int one);"
      )).to include(
          "DECLARE_FAKE_VALUE_FUNC1(char* const, bar_return_const_ptr, int)"
      )
    end

    it "works with a pointer to a const char" do
      expect(parse_and_generate_header(
        "const char * a_function();"
      )).to include(
          "DECLARE_FAKE_VALUE_FUNC0(const char*, a_function)"
      )
    end

    it "works with a pointer to a const char with alternate const position" do
      expect(parse_and_generate_header(
        "char const * a_function();"
      )).to include(
          "DECLARE_FAKE_VALUE_FUNC0(char const*, a_function)"
      )
    end

    it "works with a pointer to a const int" do
      expect(parse_and_generate_header(
        "const int * a_function();"
      )).to include(
          "DECLARE_FAKE_VALUE_FUNC0(const int*, a_function)"
      )
    end

    it "works with a pointer to a const int with alternate const position" do
      expect(parse_and_generate_header(
        "int const * a_function();"
      )).to include(
          "DECLARE_FAKE_VALUE_FUNC0(int const*, a_function)"
      )
    end
  end

  context "when there is a function that returns a const pointer" do
    let(:mock_header){
      parsed_header = parse_header("display", "const char * return_const_pointer_test_function(int value)")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the correct const return value in the declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC1(const char*, return_const_pointer_test_function, int)"
      )
    end
  end

  context "when there is a function that returns a const int" do
    let(:mock_header){
      parsed_header = parse_header("display", "const int return_const_int_test_function()")
      FffMockGenerator.create_mock_header("display", "mock_display", parsed_header)
    }
    it "then the generated file contains the correct const return value in the declaration" do
      expect(mock_header).to include(
        "DECLARE_FAKE_VALUE_FUNC0(const int, return_const_int_test_function)"
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

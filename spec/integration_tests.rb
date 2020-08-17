
# Run the cmd. Raise an exception and print the output if it fails.
def run(cmd)
  output = `#{cmd}`
  unless $?.exitstatus == 0
    puts output
    raise "Command failed: #{cmd}"
  end
end

describe "command line integration tests" do

    it "passes all tests from the command line" do
      Dir.chdir("build/integration_test") do
        run("ceedling")
      end
    end

    it "handles the verbosity argument" do
      Dir.chdir("build/integration_test") do
        run ("ceedling verbosity[4] test:all")
      end
    end

    it "handles the options argument" do
      Dir.chdir("build/integration_test") do
        run("ceedling options:special_config test:all")
      end
    end
end

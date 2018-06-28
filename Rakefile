require 'rake'
require 'rspec/core/rake_task'

desc "Run all rspecs"
RSpec::Core::RakeTask.new(:spec) do |t|
  t.pattern = Dir.glob('spec/**/*_spec.rb')
  t.rspec_opts = '--format documentation'
  # t.rspec_opts << ' more options'
end

FFF_PLUGIN_DIR = "build/integration_test/vendor/ceedling/plugins/fake_function_framework"

def run_integration_test
  chdir "build" do
    # Create a new Ceedling project.
    sh "ceedling new integration_test"
  end

  # Copy over the example project files.
  cp_r "examples/fff_example/src/.", "build/integration_test/src"
  cp_r "examples/fff_example/test/.", "build/integration_test/test"
  cp "examples/fff_example/project.yml", "build/integration_test"

  # Remove the fake_function_framework plugin folder (if it exists) from the new
  # projet.
  rm_rf FFF_PLUGIN_DIR

  # Recreate the plugin folder.
  mkdir_p FFF_PLUGIN_DIR

  # Copy over the source from this fff plugin instance.
  cp_r "lib", FFF_PLUGIN_DIR
  cp_r "src", FFF_PLUGIN_DIR
  cp_r "vendor", FFF_PLUGIN_DIR

  chdir("build/integration_test") do
      sh "ceedling clobber"
      sh "ceedling test:all"
  end
end

desc "Run integration test on example"
task :integration_test do
# Remove any exsiting build files.
  rm_rf "build"

  # Create a new build folder.
  mkdir_p "build"
  run_integration_test

end

desc "Clean build"
task :clean do
  rm_rf "build"
end

# Only run the rspec tests by default.
task :default => [:spec, :integration_test]

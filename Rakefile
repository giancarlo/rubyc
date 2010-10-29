
$: << 'lib/make'

require "make.rb"

library :librubyc do |l|
	l.output = 'build/librubyc.a'
	l.source = Dir.glob('src/lib/*.cc')
	l.cflags  = '-Iinclude -Wall'

	l.compile
end

binary :test => :librubyc do |l|
	l.source = [ '../src/test/scanner.cc' ]
	l.output = 'scanner'
	l.ldflags = '-L../build -lrubyc -lm -lstdc++'
	l.cflags = '-I../include'

	Dir.chdir('test') do
		l.compile
		`./scanner`
	end
end

desc "Default Action(Test)."
task :default => [:librubyc] 

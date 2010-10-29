#
#
#

require 'compiler'
require 'source'
require 'project'
require 'library'

module Make
	
	Compilers = {
		:c => GCC,
		:cpp => GPP
	}

	def self.verbose
		
	end

	def self.cmd(c)
		puts c
		`#{c}`
	end

	def self.language(file)
		case(File.extname(file))
		when '.c' 
			:c
		when '.cc', '.cpp' 
			:cpp
		end
	end

	def self.compiler_for(file)
		Compilers[language(file)]
	end

	def self.compile(file, flags)
		compiler_for(file).new.compile(file, flags)
	end

	def self.obj(file)
		compiler_for(file).obj(file)
	end

	def self.ar(cmd)
		cmd "ar #{cmd}" 
	end

	def self.link(cmd)
		cmd "gcc #{cmd}"
	end

end

def library *name, &block
	Make::LibraryProject.define_task(*name, &block)
end

def binary *name, &block
	Make::Project.define_task(*name, &block)
end


module Make

	class Compiler

		attr_accessor :flags, :bin

		def initialize
			@flags = ''
		end

		def mkdir(dir)
			cmd "mkdir #{dir}"
		end


		def self.obj(file)
			n = File.basename(file, File.extname(file))
			"#{n}.o"
		end

		def obj(file)
			Compiler.obj(file)
		end

		def compile(src, flags=@flags)
			case (src)
			when String
				o = obj(src)
				Make.cmd "#{bin} #{flags} -o #{o} -c #{src}"
			when Array
				src.each { |s| compile(s, flags) }
			end
		end

	end

	class GCC < Compiler

		def initialize
			@bin = 'gcc'
		end
		
	end

	class GPP < Compiler
		
		def initialize
			@bin = "g++"
		end
	end

end

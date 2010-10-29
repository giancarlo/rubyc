#
#
#

module Make

	class Project < Rake::Task

		attr_accessor :output, :source, :cflags, :outdir, :ldflags, :compiler

		def ar(cmd)
			Make.ar(cmd)
		end

		def link(files, ldflags)
			files = files.join(' ')
			Make.link("-o #{output} #{files} #{ldflags}")
		end

		def compile
			link compile_files, ldflags
		end

		def compile_files
			source.collect do |src| 
				SourceFile.new(src).compile(cflags) 
			end
		end

	end

end

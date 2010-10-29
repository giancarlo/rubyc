

module Make

	class LibraryProject < Project

		def compile
			objs = compile_files.join(' ')
			ar "rcs #{output} #{objs}"
		end

	end

end

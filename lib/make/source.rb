
module Make

	class SourceFile
		
		attr_accessor :filename, :obj

		def initialize(name)
			@filename = name
		end

		def obj
			@obj.nil? ? @obj = Make.obj(@filename) : @obj
		end
		
		def changed?
			File.exists?(obj) ? File.mtime(@filename) > File.mtime(obj) : true
		end

		def to_str
			@filename
		end

		def language
			Make.language(@filename)
		end

		def compile(flags)
			Make.compile(@filename, flags) if changed?
			obj
		end

	end

end

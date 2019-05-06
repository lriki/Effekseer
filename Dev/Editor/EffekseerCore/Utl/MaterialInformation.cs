using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

namespace Effekseer.Utl
{
#if MATERIAL_ENABLED
	public class MaterialInformation
	{
		public TextureInformation[] Textures;

		public UniformInformation[] Uniforms;

		public void Load(string path)
		{
			var jsonText = System.IO.File.ReadAllText(path);

			var parsed = JObject.Parse(jsonText);

			var guid = parsed["GUID"].Value<double>();
			var params_ = parsed["Params"];
			var uniforms_ = params_["Uniforms"] as JArray;
			var textures_ = params_["Textures"] as JArray;

			List<TextureInformation> textures = new List<TextureInformation>();

			foreach (var texture in textures_)
			{
				var name = texture["Name"].Value<string>();
				var offset = texture["Index"].Value<double>();
				var defaultPath = texture["DefaultPath"].Value<double>();
				var isParam = texture["IsParam"].Value<bool>();

				var info = new TextureInformation();

				textures.Add(info);
			}

			Textures = textures.ToArray();

			List<UniformInformation> uniforms = new List<UniformInformation>();

			foreach (var uniform in uniforms_)
			{
				var name = uniform["Name"].Value<string>();
				var offset = uniform["Offset"].Value<double>();
				var type = uniform["Type"].Value<double>();
				var defaultValue1 = uniform["DefaultValue1"].Value<double>();
				var defaultValue2 = uniform["DefaultValue2"].Value<double>();
				var defaultValue3 = uniform["DefaultValue3"].Value<double>();
				var defaultValue4 = uniform["DefaultValue4"].Value<double>();

				var info = new UniformInformation();
				info.Name = name;
				info.Offset = (int)offset;
				info.Type = (int)type;
				info.DefaultValues[0] = (float)defaultValue1;
				info.DefaultValues[1] = (float)defaultValue2;
				info.DefaultValues[2] = (float)defaultValue3;
				info.DefaultValues[3] = (float)defaultValue4;

				uniforms.Add(info);
			}

			Uniforms = Uniforms.ToArray();
		}

		public class TextureInformation
		{
			public string Name;
			public int Index;
			public string DefaultPath;
			public bool IsParam;
		}

		public class UniformInformation
		{
			public string Name;
			public int Offset;
			public int Type = 0;
			public float[] DefaultValues = new float[4];
		}
	}
#endif
}

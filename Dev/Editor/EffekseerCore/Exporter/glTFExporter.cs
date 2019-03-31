using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Effekseer.Exporter
{
	public class glTFExporter
	{
		public bool Export(string path)
		{
			Dictionary<string, object> gltf = new Dictionary<string, object>();

			gltf.Add("extensionsUsed", new object[] { "Effekseer" });

			Dictionary<string, object> extentions = new Dictionary<string, object>();

			gltf.Add("extentions", extentions);

			var effekseerExtention = new EffekseerExtention();

			var binaryExporter = new Binary.Exporter();
			var binary = binaryExporter.Export(1);

			SortedSet<string> textures = new SortedSet<string>();

			foreach(var texture in binaryExporter.UsedTextures)
			{
				textures.Add(texture);
			}

			foreach (var texture in binaryExporter.UsedNormalTextures)
			{
				textures.Add(texture);
			}

			foreach (var texture in binaryExporter.UsedDistortionTextures)
			{
				textures.Add(texture);
			}

			effekseerExtention.textures = textures.ToArray();

			extentions.Add("Effekseer", effekseerExtention);

			string json = JsonConvert.SerializeObject(gltf);

			System.IO.File.WriteAllText(path, json);

			return true;
		}

		class EffekseerExtention
		{
			public string[] textures = new string[0];
		}
	}
}

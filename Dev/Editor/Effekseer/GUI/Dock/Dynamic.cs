using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

#if MATERIAL_ENABLED
namespace Effekseer.GUI.Dock
{
	class Dynamic : DockPanel
	{
		Component.ParameterList paramerterList = null;

		bool isFiestUpdate = true;

		public Dynamic()
		{
			Label = Resources.GetString("Culling") + "###Dynamic";

			paramerterList = new Component.ParameterList();
			
			Core.OnBeforeLoad += Core_OnBeforeLoad;
			Core.OnBeforeNew += Core_OnBeforeNew;
			Core.OnAfterLoad += OnAfterLoad;
			Core.OnAfterNew += OnAfterLoad;
			Core.Dynamic.Vectors.OnChanged += Vectors_OnChanged;
			Read();

			Icon = Images.GetIcon("PanelCulling");
			IconSize = new swig.Vec2(24, 24);
			TabToolTip = Resources.GetString("Culling");
		}

		private void Vectors_OnChanged(object sender, ChangedValueEventArgs e)
		{
		}

		public void FixValues()
		{
			paramerterList.FixValues();
		}

		public override void OnDisposed()
		{
			FixValues();

			Core.OnAfterLoad -= OnAfterLoad;
			Core.OnAfterNew -= OnAfterLoad;
			Core.Dynamic.Vectors.OnChanged -= Vectors_OnChanged;
		}

		protected override void UpdateInternal()
		{
			if (isFiestUpdate)
			{
			}

			/*
			 			var v = enums.Select((_, i) => Tuple.Create(_, i)).Where(_ => _.Item1 == selectedValues).FirstOrDefault();

			if(Manager.NativeManager.BeginCombo(id, FieldNames[v.Item2], swig.ComboFlags.None, icons[v.Item2]))
			{
				for(int i = 0; i < FieldNames.Count; i++)
				{
					bool is_selected = (FieldNames[v.Item2] == FieldNames[i]);

					if (Manager.NativeManager.Selectable(FieldNames[i], is_selected, swig.SelectableFlags.None, icons[i]))
					{
						selectedValues = enums[i];
						binding.SetValue(selectedValues);
					}
						
					if (is_selected)
					{
						Manager.NativeManager.SetItemDefaultFocus();
					}

				}

			}

			 */

			var v = Core.Dynamic.Vectors.Values.Select((_, i) => Tuple.Create(_, i)).Where(_ => _.Item1 == Core.Dynamic.Vectors.Selected).FirstOrDefault();
			string selectedID = "";

			if(v != null)
			{
				selectedID = v.Item1.Name.Value + "###" + v.Item2.ToString();
			}

			if (Manager.NativeManager.BeginCombo("###Dynamic", selectedID, swig.ComboFlags.None))
			{
				for (int i = 0; i < Core.Dynamic.Vectors.Values.Count; i++)
				{
					bool is_selected = (Core.Dynamic.Vectors.Values[i] == Core.Dynamic.Vectors.Selected);

					var name = Core.Dynamic.Vectors.Values[i].Name.Value + "###" + i.ToString();

					if (Manager.NativeManager.Selectable(name, is_selected, swig.SelectableFlags.None))
					{
						Core.Dynamic.Vectors.Selected = Core.Dynamic.Vectors.Values[i];
					}

					if (is_selected)
					{
						Manager.NativeManager.SetItemDefaultFocus();
					}
				}

				Manager.NativeManager.EndCombo();
			}

			if(Manager.NativeManager.Button("Add###DynamicAdd"))
			{
				Core.Dynamic.Vectors.Add();
			}

			paramerterList.Update();
		}

		void Read()
		{
			paramerterList.SetValue(Core.Dynamic.Vectors);
		}

		private void Core_OnBeforeNew(object sender, EventArgs e)
		{
			Core.Dynamic.Vectors.OnChanged -= Vectors_OnChanged;
			paramerterList.SetValue(null);
		}

		private void Core_OnBeforeLoad(object sender, EventArgs e)
		{
			Core.Dynamic.Vectors.OnChanged -= Vectors_OnChanged;
			paramerterList.SetValue(null);
		}

		void OnAfterLoad(object sender, EventArgs e)
		{
			Core.Dynamic.Vectors.OnChanged += Vectors_OnChanged;
			Read();
		}
	}
}
#endif

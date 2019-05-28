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
		Component.ParameterList paramerterListInput = null;

		Component.ParameterList paramerterList = null;

		bool isFiestUpdate = true;

		public Dynamic()
		{
			Label = Resources.GetString("Culling") + "###Dynamic";

			paramerterListInput = new Component.ParameterList();
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
			paramerterListInput.FixValues();
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

			Manager.NativeManager.Text("Dynamic Parameter");

			paramerterListInput.Update();

			Manager.NativeManager.Separator();

			Manager.NativeManager.Text("Calculation");

			var nextParam = Component.DynamicSelector.Select(Core.Dynamic.Vectors.Selected, false, true);

			if (Core.Dynamic.Vectors.Selected != nextParam)
			{
				Core.Dynamic.Vectors.Selected = nextParam;
			}

			if(Manager.NativeManager.Button("Add###DynamicAdd"))
			{
				Core.Dynamic.Vectors.Add();
			}

			paramerterList.Update();
		}

		void Read()
		{
			paramerterListInput.SetValue(Core.Dynamic.Inputs);
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

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Effekseer.InternalScript
{
	enum OperatorType
	{
		Constant = 0,
		Add = 1,
		Sub = 2,
		Mul = 3,
		Div = 4,
	}
	class Operator
	{
		public OperatorType Type;
		public List<string> Inputs = new List<string>();
		public List<string> Outputs = new List<string>();
		public Dictionary<string, object> Attributes = new Dictionary<string, object>();
	}
	class Compiler
	{
		List<Operator> operators = new List<Operator>();

		public void Compile()
		{
			operators.Clear();
		}

		void Compile(Expression expr)
		{
			if(expr is BinOpExpression)
			{
				var e = expr as BinOpExpression;
				var o = new Operator();
				if (e.Operator == "+") o.Type = OperatorType.Add;
				if (e.Operator == "-") o.Type = OperatorType.Sub;
				if (e.Operator == "*") o.Type = OperatorType.Mul;
				if (e.Operator == "/") o.Type = OperatorType.Div;
				o.Inputs.Add(e.Lhs.ToString());
				o.Inputs.Add(e.Rhs.ToString());
				o.Outputs.Add(e.Line.ToString());
				operators.Add(o);
			}
			else if(expr is LabelExpression)
			{
				
			}
			else if(expr is NumberExpression)
			{
				var e = expr as NumberExpression;
				var o = new Operator();
				o.Type = OperatorType.Constant;
				o.Outputs.Add(e.Line.ToString());
				o.Attributes.Add("Constant", e.Value);
				operators.Add(o);
			}
		}

		string GetOutputName(Expression expr)
		{
			if(expr is LabelExpression)
			{
				var e = expr as LabelExpression;
				return e.Value;
			}
			else
			{
				return expr.Line.ToString();
			}
		}

		int GetInputIndex(Expression expr)
		{
			if(expr is LabelExpression)
			{
				var e = expr as LabelExpression;

				if (e.Value == "$1") return 0;
				if (e.Value == "$2") return 1;
				if (e.Value == "$3") return 2;
				if (e.Value == "$4") return 3;

				throw new Exception();
			}

			throw new Exception();
		}
	}
}

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

	public class Test
	{
		public Test()
		{
			Compiler compiler = new Compiler();
			compiler.Compile("1 + 2 + 3");
			compiler.Compile("1 * 2 + 3");
			compiler.Compile("1 * (2 + 3)");
		}
	}

	public class CompileResult
	{
		public byte[] Bytecode = null;
		public CompileException Error;
	}
	public class Compiler
	{
		List<Operator> operators = new List<Operator>();

		public CompileResult Compile(string code)
		{
			CompileResult compileResult = new CompileResult();

			operators.Clear();

			if(string.IsNullOrEmpty(code))
			{
				return compileResult;
			}

			// export
			List<byte[]> data = new List<byte[]>();

			try
			{
				var lexer = new Lexer();
				var tokens = lexer.Analyze(code);

				var parser = new Parser();
				var expr = parser.Parse(tokens.Tokens);

				Compile(expr);

				Dictionary<string, int> variableList = new Dictionary<string, int>();
				foreach (var opt in operators)
				{
					foreach (var o in opt.Inputs.Concat(opt.Outputs))
					{
						if (IsValidLabel(o)) continue;

						if (!variableList.ContainsKey(o))
						{
							variableList.Add(o, variableList.Count);
						}
					}
				}

				int version = 0;
				data.Add(BitConverter.GetBytes(version));
				data.Add(BitConverter.GetBytes(variableList.Count));
				data.Add(BitConverter.GetBytes(operators.Count));

				// Output register
				var outputName = GetOutputName(expr);
				if (variableList.ContainsKey(outputName))
				{
					var index = variableList[outputName];
					data.Add(BitConverter.GetBytes(index));
				}
				else
				{
					var index = GetInputIndex(outputName);
					data.Add(BitConverter.GetBytes(index));
				}

				// Operators
				foreach (var op in operators)
				{
					data.Add(BitConverter.GetBytes((int)op.Type));
					data.Add(BitConverter.GetBytes((int)op.Inputs.Count));

					foreach (var o in op.Inputs)
					{
						if (variableList.ContainsKey(o))
						{
							var index = variableList[o];
							data.Add(BitConverter.GetBytes(index));
						}
						else
						{
							var index = GetInputIndex(o);
							data.Add(BitConverter.GetBytes(index));
						}
					}

					data.Add(BitConverter.GetBytes((int)op.Outputs.Count));

					foreach (var o in op.Outputs)
					{
						if (variableList.ContainsKey(o))
						{
							var index = variableList[o];
							data.Add(BitConverter.GetBytes(index));
						}
						else
						{
							var index = GetInputIndex(o);
							data.Add(BitConverter.GetBytes(index));
						}
					}

					// Attribute
					if (op.Type == OperatorType.Constant)
					{
						data.Add(BitConverter.GetBytes(1));
						var value = (float)op.Attributes["Constant"];
						data.Add(BitConverter.GetBytes(value));
					}
					else
					{
						data.Add(BitConverter.GetBytes(0));
					}
				}
			}
			catch(CompileException e)
			{
				compileResult.Error = e;
				return compileResult;
			}

			compileResult.Bytecode = data.SelectMany(_ => _).ToArray();
			return compileResult;
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

				Compile(e.Lhs);
				Compile(e.Rhs);

				o.Inputs.Add(GetOutputName(e.Lhs));
				o.Inputs.Add(GetOutputName(e.Rhs));
				o.Outputs.Add(GetOutputName(e));
				operators.Add(o);
			}
			else if(expr is LabelExpression)
			{
				var e = expr as LabelExpression;
				if (!IsValidLabel(e.Value))
				{
					throw new CompileException(string.Format("Invalid label {0}", e.Value), e.Line);
				}

			}
			else if(expr is NumberExpression)
			{
				var e = expr as NumberExpression;
				var o = new Operator();
				o.Type = OperatorType.Constant;
				o.Outputs.Add(GetOutputName(e));
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

		bool IsValidLabel(string label)
		{
			HashSet<string> valid = new HashSet<string>();
			valid.Add("$1");
			valid.Add("$2");
			valid.Add("$3");
			valid.Add("$4");
			return valid.Contains(label);
		}

		int GetInputIndex(string label)
		{
			if (label == "$1") return 0 + 0xfff;
			if (label == "$2") return 1 + 0xfff;
			if (label == "$3") return 2 + 0xfff;
			if (label == "$4") return 3 + 0xfff;

			throw new Exception();
		}
	}
}

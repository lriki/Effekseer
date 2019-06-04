﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Effekseer.InternalScript
{
	class CompileException : System.Exception
	{
		public CompileException(string message, int line)
			: base(message)
		{
			Line = line;
		}
		public int Line
		{
			get;
			private set;
		}
	}

	class Expression
	{
		public int Line = 0;
	}

	class BinOpExpression : Expression
	{
		public string Operator = "";
		public Expression Lhs = null;
		public Expression Rhs = null;
	}

	class NumberExpression : Expression
	{
		public float Value;
		public NumberExpression(float value)
		{
			Value = value;
		}
	}

	class LabelExpression : Expression
	{
		public string Value;
		public LabelExpression(string value)
		{
			Value = value;
		}
	}


	/// <summary>
	/// 
	/// </summary>
	/// <remarks>
	/// Expr = Term {* Term, / Term}
	/// Term = Group {+ Group, - Group}
	/// Group = (Expr), Number, Label
	/// </remarks>
	class Parser
	{
		List<Token> tokens = null;
		int index = 0;

		public Expression Parse(List<Token> tokens)
		{
			this.tokens = tokens;
			index = 0;
			return Expr();
		}

		Expression Expr()
		{
			var lhs = Term();
			
			var token = Peek();

			if(token != null)
			{
				if(token.Type == TokenType.Operator && (string)token.Value == "*")
				{
					Next();
					var rhs = Term();

					var ret = new BinOpExpression();
					ret.Line = token.Line;
					ret.Lhs = lhs;
					ret.Rhs = rhs;
					ret.Operator = (string)token.Value;
					return ret;
				}
				else if (token.Type == TokenType.Operator && (string)token.Value == "/")
				{
					Next();
					var rhs = Term();

					var ret = new BinOpExpression();
					ret.Line = token.Line;
					ret.Lhs = lhs;
					ret.Rhs = rhs;
					ret.Operator = (string)token.Value;
					return ret;
				}
				else
				{
					throw new CompileException(string.Format("Invalid token {0}", token), token.Line);
				}
			}
			else
			{
				return lhs;
			}
		}

		Expression Term()
		{
			var lhs = Group();
			if (lhs == null) throw new CompileException("Unknown error", -1);

			var token = Peek();

			if (token != null)
			{
				if (token.Type == TokenType.Operator && (string)token.Value == "+")
				{
					Next();
					var rhs = Group();

					var ret = new BinOpExpression();
					ret.Line = token.Line;
					ret.Lhs = lhs;
					ret.Rhs = rhs;
					ret.Operator = (string)token.Value;
					return ret;
				}
				else if (token.Type == TokenType.Operator && (string)token.Value == "-")
				{
					Next();
					var rhs = Group();

					var ret = new BinOpExpression();
					ret.Line = token.Line;
					ret.Lhs = lhs;
					ret.Rhs = rhs;
					ret.Operator = (string)token.Value;
					return ret;
				}
				else
				{
					throw new CompileException(string.Format("Invalid token {0}", token), token.Line);
				}
			}
			else
			{
				return lhs;
			}
		}

		Expression Group()
		{
			var token = Peek();

			if(token != null)
			{
				if(token.Type == TokenType.LeftParentheses)
				{
					Next();
					var center = Expr();
					var right = Next();

					if(right != null && right.Type == TokenType.RightParentheses)
					{
						return center;
					}
					else
					{
						if(token == null)
						{
							throw new CompileException(string.Format("Invalid EOF"), token.Line);
						}

						throw new CompileException(string.Format("Invalid token {0}", token), token.Line);
					}
				}
				else if(token.Type == TokenType.Label)
				{
					Next();
					var ret = new LabelExpression((string)token.Value);
					ret.Line = token.Line;
					return ret;
				}
				else if (token.Type == TokenType.Digit)
				{
					Next();
					var ret = new NumberExpression((float)token.Value);
					ret.Line = token.Line;
					return ret;
				}
				else
				{
					throw new CompileException(string.Format("Invalid token {0}", token), token.Line);
				}
			}
			else
			{
				throw new CompileException(string.Format("Invalid EOF"), token.Line);
			}
		}

		Token Peek()
		{
			if(tokens.Count() > index)
			{
				return tokens[index];
			}
			return null;
		}

		Token Next()
		{
			index++;
			return Peek();
		}
	}
}
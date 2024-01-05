// Generated from E:/Git/PL0Compiler/PL0-java/src/main/java/org/example/antlr/PL0.g4 by ANTLR 4.13.1
package org.example.antlr.PL0;
import org.antlr.v4.runtime.tree.ParseTreeVisitor;

/**
 * This interface defines a complete generic visitor for a parse tree produced
 * by {@link PL0Parser}.
 *
 * @param <T> The return type of the visit operation. Use {@link Void} for
 * operations with no return type.
 */
public interface PL0Visitor<T> extends ParseTreeVisitor<T> {
	/**
	 * Visit a parse tree produced by {@link PL0Parser#start}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStart(PL0Parser.StartContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#program}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgram(PL0Parser.ProgramContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#programHead}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitProgramHead(PL0Parser.ProgramHeadContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#block}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitBlock(PL0Parser.BlockContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#constantSpecification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstantSpecification(PL0Parser.ConstantSpecificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#constantDefinition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitConstantDefinition(PL0Parser.ConstantDefinitionContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#uint}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitUint(PL0Parser.UintContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#varSpecification}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitVarSpecification(PL0Parser.VarSpecificationContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#identifier}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIdentifier(PL0Parser.IdentifierContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCompoundStatement(PL0Parser.CompoundStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#statement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitStatement(PL0Parser.StatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#nullStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitNullStatement(PL0Parser.NullStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAssignmentStatement(PL0Parser.AssignmentStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#expression}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitExpression(PL0Parser.ExpressionContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#item}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitItem(PL0Parser.ItemContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#factor}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitFactor(PL0Parser.FactorContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#addOperator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitAddOperator(PL0Parser.AddOperatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#mulOperator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitMulOperator(PL0Parser.MulOperatorContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#ifStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitIfStatement(PL0Parser.IfStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#whileStatement}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitWhileStatement(PL0Parser.WhileStatementContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#condition}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitCondition(PL0Parser.ConditionContext ctx);
	/**
	 * Visit a parse tree produced by {@link PL0Parser#relationOperator}.
	 * @param ctx the parse tree
	 * @return the visitor result
	 */
	T visitRelationOperator(PL0Parser.RelationOperatorContext ctx);
}
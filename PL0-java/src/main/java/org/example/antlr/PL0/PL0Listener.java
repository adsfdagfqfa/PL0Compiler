// Generated from D:/CodeField/Java/compiling/ANTLR-TEST-2/src/antlr/PL0.g4 by ANTLR 4.13.1
package PL0;
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link PL0Parser}.
 */
public interface PL0Listener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link PL0Parser#start}.
	 * @param ctx the parse tree
	 */
	void enterStart(PL0Parser.StartContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#start}.
	 * @param ctx the parse tree
	 */
	void exitStart(PL0Parser.StartContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(PL0Parser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(PL0Parser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#programHead}.
	 * @param ctx the parse tree
	 */
	void enterProgramHead(PL0Parser.ProgramHeadContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#programHead}.
	 * @param ctx the parse tree
	 */
	void exitProgramHead(PL0Parser.ProgramHeadContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#block}.
	 * @param ctx the parse tree
	 */
	void enterBlock(PL0Parser.BlockContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#block}.
	 * @param ctx the parse tree
	 */
	void exitBlock(PL0Parser.BlockContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#constantSpecification}.
	 * @param ctx the parse tree
	 */
	void enterConstantSpecification(PL0Parser.ConstantSpecificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#constantSpecification}.
	 * @param ctx the parse tree
	 */
	void exitConstantSpecification(PL0Parser.ConstantSpecificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#constantDefinition}.
	 * @param ctx the parse tree
	 */
	void enterConstantDefinition(PL0Parser.ConstantDefinitionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#constantDefinition}.
	 * @param ctx the parse tree
	 */
	void exitConstantDefinition(PL0Parser.ConstantDefinitionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#uint}.
	 * @param ctx the parse tree
	 */
	void enterUint(PL0Parser.UintContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#uint}.
	 * @param ctx the parse tree
	 */
	void exitUint(PL0Parser.UintContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#varSpecification}.
	 * @param ctx the parse tree
	 */
	void enterVarSpecification(PL0Parser.VarSpecificationContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#varSpecification}.
	 * @param ctx the parse tree
	 */
	void exitVarSpecification(PL0Parser.VarSpecificationContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#identifier}.
	 * @param ctx the parse tree
	 */
	void enterIdentifier(PL0Parser.IdentifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#identifier}.
	 * @param ctx the parse tree
	 */
	void exitIdentifier(PL0Parser.IdentifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void enterCompoundStatement(PL0Parser.CompoundStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#compoundStatement}.
	 * @param ctx the parse tree
	 */
	void exitCompoundStatement(PL0Parser.CompoundStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void enterStatement(PL0Parser.StatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#statement}.
	 * @param ctx the parse tree
	 */
	void exitStatement(PL0Parser.StatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#nullStatement}.
	 * @param ctx the parse tree
	 */
	void enterNullStatement(PL0Parser.NullStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#nullStatement}.
	 * @param ctx the parse tree
	 */
	void exitNullStatement(PL0Parser.NullStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void enterAssignmentStatement(PL0Parser.AssignmentStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#assignmentStatement}.
	 * @param ctx the parse tree
	 */
	void exitAssignmentStatement(PL0Parser.AssignmentStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void enterExpression(PL0Parser.ExpressionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#expression}.
	 * @param ctx the parse tree
	 */
	void exitExpression(PL0Parser.ExpressionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#item}.
	 * @param ctx the parse tree
	 */
	void enterItem(PL0Parser.ItemContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#item}.
	 * @param ctx the parse tree
	 */
	void exitItem(PL0Parser.ItemContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void enterFactor(PL0Parser.FactorContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#factor}.
	 * @param ctx the parse tree
	 */
	void exitFactor(PL0Parser.FactorContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#addOperator}.
	 * @param ctx the parse tree
	 */
	void enterAddOperator(PL0Parser.AddOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#addOperator}.
	 * @param ctx the parse tree
	 */
	void exitAddOperator(PL0Parser.AddOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#mulOperator}.
	 * @param ctx the parse tree
	 */
	void enterMulOperator(PL0Parser.MulOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#mulOperator}.
	 * @param ctx the parse tree
	 */
	void exitMulOperator(PL0Parser.MulOperatorContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void enterIfStatement(PL0Parser.IfStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#ifStatement}.
	 * @param ctx the parse tree
	 */
	void exitIfStatement(PL0Parser.IfStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void enterWhileStatement(PL0Parser.WhileStatementContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#whileStatement}.
	 * @param ctx the parse tree
	 */
	void exitWhileStatement(PL0Parser.WhileStatementContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void enterCondition(PL0Parser.ConditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#condition}.
	 * @param ctx the parse tree
	 */
	void exitCondition(PL0Parser.ConditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link PL0Parser#relationOperator}.
	 * @param ctx the parse tree
	 */
	void enterRelationOperator(PL0Parser.RelationOperatorContext ctx);
	/**
	 * Exit a parse tree produced by {@link PL0Parser#relationOperator}.
	 * @param ctx the parse tree
	 */
	void exitRelationOperator(PL0Parser.RelationOperatorContext ctx);
}
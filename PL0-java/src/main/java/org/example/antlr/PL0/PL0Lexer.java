// Generated from D:/CodeField/Java/compiling/ANTLR-TEST-2/src/antlr/PL0.g4 by ANTLR 4.13.1
package PL0;
import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class PL0Lexer extends Lexer {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		T__0=1, T__1=2, T__2=3, T__3=4, T__4=5, T__5=6, T__6=7, T__7=8, T__8=9, 
		T__9=10, T__10=11, T__11=12, T__12=13, T__13=14, T__14=15, T__15=16, T__16=17, 
		T__17=18, T__18=19, T__19=20, T__20=21, T__21=22, T__22=23, T__23=24, 
		NUMBER=25, LETTER=26, WS=27;
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
			"T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
			"T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "NUMBER", 
			"LETTER", "WS"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'PROGRAM'", "'CONST'", "','", "';'", "':='", "'VAR'", "'BEGIN'", 
			"'END'", "'+'", "'-'", "'('", "')'", "'*'", "'/'", "'IF'", "'THEN'", 
			"'WHILE'", "'DO'", "'='", "'<>'", "'<'", "'<='", "'>'", "'>='"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, null, null, null, null, null, null, null, null, null, null, null, 
			null, "NUMBER", "LETTER", "WS"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}


	public PL0Lexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "PL0.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u0000\u001b\u0091\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002"+
		"\u0001\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002"+
		"\u0004\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002"+
		"\u0007\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002"+
		"\u000b\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e"+
		"\u0002\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011"+
		"\u0002\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014"+
		"\u0002\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017"+
		"\u0002\u0018\u0007\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0003\u0001\u0003"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001"+
		"\b\u0001\t\u0001\t\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\f\u0001"+
		"\f\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u0010\u0001\u0010\u0001"+
		"\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001"+
		"\u0011\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001"+
		"\u0014\u0001\u0014\u0001\u0015\u0001\u0015\u0001\u0015\u0001\u0016\u0001"+
		"\u0016\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0018\u0001\u0018\u0001"+
		"\u0019\u0001\u0019\u0001\u001a\u0004\u001a\u008c\b\u001a\u000b\u001a\f"+
		"\u001a\u008d\u0001\u001a\u0001\u001a\u0000\u0000\u001b\u0001\u0001\u0003"+
		"\u0002\u0005\u0003\u0007\u0004\t\u0005\u000b\u0006\r\u0007\u000f\b\u0011"+
		"\t\u0013\n\u0015\u000b\u0017\f\u0019\r\u001b\u000e\u001d\u000f\u001f\u0010"+
		"!\u0011#\u0012%\u0013\'\u0014)\u0015+\u0016-\u0017/\u00181\u00193\u001a"+
		"5\u001b\u0001\u0000\u0003\u0001\u000009\u0001\u0000az\u0003\u0000\t\n"+
		"\r\r  \u0091\u0000\u0001\u0001\u0000\u0000\u0000\u0000\u0003\u0001\u0000"+
		"\u0000\u0000\u0000\u0005\u0001\u0000\u0000\u0000\u0000\u0007\u0001\u0000"+
		"\u0000\u0000\u0000\t\u0001\u0000\u0000\u0000\u0000\u000b\u0001\u0000\u0000"+
		"\u0000\u0000\r\u0001\u0000\u0000\u0000\u0000\u000f\u0001\u0000\u0000\u0000"+
		"\u0000\u0011\u0001\u0000\u0000\u0000\u0000\u0013\u0001\u0000\u0000\u0000"+
		"\u0000\u0015\u0001\u0000\u0000\u0000\u0000\u0017\u0001\u0000\u0000\u0000"+
		"\u0000\u0019\u0001\u0000\u0000\u0000\u0000\u001b\u0001\u0000\u0000\u0000"+
		"\u0000\u001d\u0001\u0000\u0000\u0000\u0000\u001f\u0001\u0000\u0000\u0000"+
		"\u0000!\u0001\u0000\u0000\u0000\u0000#\u0001\u0000\u0000\u0000\u0000%"+
		"\u0001\u0000\u0000\u0000\u0000\'\u0001\u0000\u0000\u0000\u0000)\u0001"+
		"\u0000\u0000\u0000\u0000+\u0001\u0000\u0000\u0000\u0000-\u0001\u0000\u0000"+
		"\u0000\u0000/\u0001\u0000\u0000\u0000\u00001\u0001\u0000\u0000\u0000\u0000"+
		"3\u0001\u0000\u0000\u0000\u00005\u0001\u0000\u0000\u0000\u00017\u0001"+
		"\u0000\u0000\u0000\u0003?\u0001\u0000\u0000\u0000\u0005E\u0001\u0000\u0000"+
		"\u0000\u0007G\u0001\u0000\u0000\u0000\tI\u0001\u0000\u0000\u0000\u000b"+
		"L\u0001\u0000\u0000\u0000\rP\u0001\u0000\u0000\u0000\u000fV\u0001\u0000"+
		"\u0000\u0000\u0011Z\u0001\u0000\u0000\u0000\u0013\\\u0001\u0000\u0000"+
		"\u0000\u0015^\u0001\u0000\u0000\u0000\u0017`\u0001\u0000\u0000\u0000\u0019"+
		"b\u0001\u0000\u0000\u0000\u001bd\u0001\u0000\u0000\u0000\u001df\u0001"+
		"\u0000\u0000\u0000\u001fi\u0001\u0000\u0000\u0000!n\u0001\u0000\u0000"+
		"\u0000#t\u0001\u0000\u0000\u0000%w\u0001\u0000\u0000\u0000\'y\u0001\u0000"+
		"\u0000\u0000)|\u0001\u0000\u0000\u0000+~\u0001\u0000\u0000\u0000-\u0081"+
		"\u0001\u0000\u0000\u0000/\u0083\u0001\u0000\u0000\u00001\u0086\u0001\u0000"+
		"\u0000\u00003\u0088\u0001\u0000\u0000\u00005\u008b\u0001\u0000\u0000\u0000"+
		"78\u0005P\u0000\u000089\u0005R\u0000\u00009:\u0005O\u0000\u0000:;\u0005"+
		"G\u0000\u0000;<\u0005R\u0000\u0000<=\u0005A\u0000\u0000=>\u0005M\u0000"+
		"\u0000>\u0002\u0001\u0000\u0000\u0000?@\u0005C\u0000\u0000@A\u0005O\u0000"+
		"\u0000AB\u0005N\u0000\u0000BC\u0005S\u0000\u0000CD\u0005T\u0000\u0000"+
		"D\u0004\u0001\u0000\u0000\u0000EF\u0005,\u0000\u0000F\u0006\u0001\u0000"+
		"\u0000\u0000GH\u0005;\u0000\u0000H\b\u0001\u0000\u0000\u0000IJ\u0005:"+
		"\u0000\u0000JK\u0005=\u0000\u0000K\n\u0001\u0000\u0000\u0000LM\u0005V"+
		"\u0000\u0000MN\u0005A\u0000\u0000NO\u0005R\u0000\u0000O\f\u0001\u0000"+
		"\u0000\u0000PQ\u0005B\u0000\u0000QR\u0005E\u0000\u0000RS\u0005G\u0000"+
		"\u0000ST\u0005I\u0000\u0000TU\u0005N\u0000\u0000U\u000e\u0001\u0000\u0000"+
		"\u0000VW\u0005E\u0000\u0000WX\u0005N\u0000\u0000XY\u0005D\u0000\u0000"+
		"Y\u0010\u0001\u0000\u0000\u0000Z[\u0005+\u0000\u0000[\u0012\u0001\u0000"+
		"\u0000\u0000\\]\u0005-\u0000\u0000]\u0014\u0001\u0000\u0000\u0000^_\u0005"+
		"(\u0000\u0000_\u0016\u0001\u0000\u0000\u0000`a\u0005)\u0000\u0000a\u0018"+
		"\u0001\u0000\u0000\u0000bc\u0005*\u0000\u0000c\u001a\u0001\u0000\u0000"+
		"\u0000de\u0005/\u0000\u0000e\u001c\u0001\u0000\u0000\u0000fg\u0005I\u0000"+
		"\u0000gh\u0005F\u0000\u0000h\u001e\u0001\u0000\u0000\u0000ij\u0005T\u0000"+
		"\u0000jk\u0005H\u0000\u0000kl\u0005E\u0000\u0000lm\u0005N\u0000\u0000"+
		"m \u0001\u0000\u0000\u0000no\u0005W\u0000\u0000op\u0005H\u0000\u0000p"+
		"q\u0005I\u0000\u0000qr\u0005L\u0000\u0000rs\u0005E\u0000\u0000s\"\u0001"+
		"\u0000\u0000\u0000tu\u0005D\u0000\u0000uv\u0005O\u0000\u0000v$\u0001\u0000"+
		"\u0000\u0000wx\u0005=\u0000\u0000x&\u0001\u0000\u0000\u0000yz\u0005<\u0000"+
		"\u0000z{\u0005>\u0000\u0000{(\u0001\u0000\u0000\u0000|}\u0005<\u0000\u0000"+
		"}*\u0001\u0000\u0000\u0000~\u007f\u0005<\u0000\u0000\u007f\u0080\u0005"+
		"=\u0000\u0000\u0080,\u0001\u0000\u0000\u0000\u0081\u0082\u0005>\u0000"+
		"\u0000\u0082.\u0001\u0000\u0000\u0000\u0083\u0084\u0005>\u0000\u0000\u0084"+
		"\u0085\u0005=\u0000\u0000\u00850\u0001\u0000\u0000\u0000\u0086\u0087\u0007"+
		"\u0000\u0000\u0000\u00872\u0001\u0000\u0000\u0000\u0088\u0089\u0007\u0001"+
		"\u0000\u0000\u00894\u0001\u0000\u0000\u0000\u008a\u008c\u0007\u0002\u0000"+
		"\u0000\u008b\u008a\u0001\u0000\u0000\u0000\u008c\u008d\u0001\u0000\u0000"+
		"\u0000\u008d\u008b\u0001\u0000\u0000\u0000\u008d\u008e\u0001\u0000\u0000"+
		"\u0000\u008e\u008f\u0001\u0000\u0000\u0000\u008f\u0090\u0006\u001a\u0000"+
		"\u0000\u00906\u0001\u0000\u0000\u0000\u0002\u0000\u008d\u0001\u0006\u0000"+
		"\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}
#include <QDebug>
#include <QApplication>
#include <QMainWindow>
#include <QDesktopWidget>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <iostream>
#include "qinputeventrecorder.h"
#include "application.h"
#include "optionparser.h"


// -c --core         : try with Core Profile
// -p --comp         : try with Compatibility Profile
// -f --defp         : try with Default Profile
// -d --debug        : try with Debug Context
// -j --majv         : requested OpenGL major version
// -n --minv         : requested OpenGL minor version
// -e xx --depth=xx  : select depth (default 16)
// -t --threaded     : run with threaded renderer
// -s --sample=xx    : enable xx sample buffers
// -f --fullscreen   : start as a fullscreen window
//    --save         : save settings as defaults
//    --clear        : clear settings

static long num(const option::Option &option)
{
	char *endptr = NULL;
	if ( option.arg != 0 )
 		return strtol(option.arg, &endptr, 10);
	return 0;
}

struct Arg: public option::Arg
{
	static void printError(const char* msg1, const option::Option& opt, const char* msg2)
	{
	  fprintf(stderr, "ERROR: %s", msg1);
	  fwrite(opt.name, opt.namelen, 1, stderr);
	  fprintf(stderr, "%s", msg2);
	}
	
	static option::ArgStatus Unknown(const option::Option& option, bool msg)
	{
	  if (msg) printError("Unknown option '", option, "'\n");
	  return option::ARG_ILLEGAL;
	}
	
	static option::ArgStatus Required(const option::Option& option, bool msg)
	{
	  if (option.arg != 0)
	    return option::ARG_OK;
	
	  if (msg) printError("Option '", option, "' requires an argument\n");
	  return option::ARG_ILLEGAL;
	}
	
	static option::ArgStatus NonEmpty(const option::Option& option, bool msg)
	{
	  if (option.arg != 0 && option.arg[0] != 0)
	    return option::ARG_OK;
	
	  if (msg) printError("Option '", option, "' requires a non-empty argument\n");
	  return option::ARG_ILLEGAL;
	}
	
	static option::ArgStatus Numeric(const option::Option& option, bool msg)
	{
	  char* endptr = 0;
	  if (option.arg != 0 && strtol(option.arg, &endptr, 10)){};
	  if (endptr != option.arg && *endptr == 0)
	    return option::ARG_OK;
	
	  if (msg) printError("Option '", option, "' requires a numeric argument\n");
	  return option::ARG_ILLEGAL;
	}
};

enum  optionIndex { UNKNOWN, HELP, CORE, COMP, DEFP, MAJV, MINV, DEPTH, DEBUG };
const option::Descriptor usage[] =
{
    {UNKNOWN, 0,"" , ""    , option::Arg::None, "USAGE: example [options]\n\n"
                                                "Options:" },
    {HELP,    0,"" , "help", option::Arg::None, "  --help, -h  \tPrint usage and exit." },
    {CORE,    0,"c", "core", option::Arg::None, "  --core, -c  \tCore profile (sel. one)." },
    {COMP,    0,"p", "comp", option::Arg::None, "  --comp, -p  \tCompability profile (sel. one)." },
    {DEFP,    0,"f", "defp", option::Arg::None, "  --defp, -f  \tDefault profile (sel. one)." },
    {MAJV,    0,"j", "majv", Arg::Numeric,      "  --majv, -j  \tOpenGL major version." },
    {MINV,    0,"n", "minv", Arg::Numeric,      "  --minv, -n  \tOpenGL minor version." },
    {DEPTH,   0,"e", "depth",Arg::Numeric,      "  --depth,-e  \tSelect depth buffer." },
    {DEBUG,   0,"d", "debug",option::Arg::None, "  --debug,-d  \tDebug run." },
    {UNKNOWN, 0,"" ,  ""   , option::Arg::None, "\nExamples:\n"
                                               "  example --unknown -- --this_is_no_option\n"
                                               "  example -unk --plus -ppp file1 file2\n" },
    {0,0,0,0,0,0}
};



int main( int argc, char ** argv )
{
    QApplication a( argc, argv );

    argc-=(argc>0); argv+=(argc>0); // skip program name argv[0] if present
    option::Stats  stats(usage, argc, argv);
    QVector<option::Option> options(stats.options_max), buffer(stats.buffer_max);
    option::Parser parse(usage, argc, argv, options.data(), buffer.data());

    if (parse.error())
        return 1;

    if (options[HELP]) {
        option::printUsage(std::cout, usage);
        return 0;
    }
 
    // Specify default format:
    QSurfaceFormat format;
    int majv = 0, minv = 0;
    if (options[MAJV]) {
    	majv = num( options[MAJV] );
    	if (options[MAJV])
    		minv = num( options[MINV] );
		format.setVersion( majv, minv );
    }
    if (options[CORE] && !options[COMP] && !options[DEFP]) {
      format.setProfile( QSurfaceFormat::CoreProfile );
    } else if (!options[CORE] && options[COMP] && !options[DEFP]) {
      format.setProfile( QSurfaceFormat::CompatibilityProfile );
    } else if (!options[CORE] && !options[COMP] && options[DEFP]) {
      format.setProfile( QSurfaceFormat::NoProfile );
    } else if (!options[CORE] && !options[COMP] && !options[DEFP]) {
      format.setProfile( QSurfaceFormat::NoProfile );
    } else {
    	// all other combinatinos are invalid
        option::printUsage(std::cout, usage);
        return 0;
    }

#ifdef _DEBUG
    format.setOption( QSurfaceFormat::DebugContext );
#else
    if (options[DEBUG]) {
      format.setOption( QSurfaceFormat::DebugContext );
    }
#endif
    format.setDepthBufferSize(16);
    format.setSamples( true );
    QSurfaceFormat::setDefaultFormat(format);
    QApplication::setAttribute( Qt::AA_ShareOpenGLContexts );
    // Retina display support for Mac OS, iOS and X11:
    // http://blog.qt.digia.com/blog/2013/04/25/retina-display-support-for-mac-os-ios-and-x11/
    //
    // AA_UseHighDpiPixmaps attribute is off by default in Qt 5.1 but will most
    // likely be on by default in a future release of Qt.
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // end.

    QScopedPointer<Application> app(new Application);

    QIcon appIcon;
    appIcon.addFile(":/icons/icon-32.png");
    appIcon.addFile(":/icons/icon-128.png");
    app->setWindowIcon(appIcon);

    QPoint pos = QApplication::desktop()->availableGeometry().topLeft() + QPoint(200, 200);
    app->resize(QSize(640, 480));
    app->move(pos);
    app->show();

    return a.exec();
}

\documentclass[a4paper]{report}

% Encoding goes first because it effects how other packages work
\usepackage[utf8]{inputenc}
\usepackage[T1]{fontenc}

\usepackage[english]{babel} %language selection
\selectlanguage{english}

\pagenumbering{arabic}

\usepackage{hyperref}
\hypersetup{colorlinks, 
           citecolor=black,
           filecolor=black,
           linkcolor=black,
           urlcolor=black,
           bookmarksopen=true,
           pdftex}

\hfuzz = .6pt % avoid black boxes

% Fonts
\usepackage{courier}
\usepackage{tgbonum}
%\usepackage{inconsolata}

\usepackage{geometry}
\usepackage{multicol}
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{listings}
\usepackage{hyperref}
\usepackage{natbib}
\usepackage{fancyhdr}
\usepackage{imakeidx}
\usepackage{graphicx}
\usepackage{color}
\usepackage{xcolor}
\usepackage{longtable}
\usepackage{booktabs}

\DeclareUnicodeCharacter{0008}{ }

\geometry{
    margin=1.4in,
    marginparwidth=0.8in
}

% Constants that are redefined
\newcommand{\embversion}{2.0.0-alpha4}
\newcommand{\version}{\embversion}
\newcommand{\libembversion}{1.0.0-alpha}
\newcommand{\publicationdate}{August 2023}

% Marginalia
\newcommand{\todo}[1]{\marginpar{\emph{TODO}\\{\footnotesize #1}}}

\makeindex

\title{Embroidermodder Reference Manual \embversion}
\author{The Embroidermodder Team}

\lstset{
  basicstyle=\ttfamily\footnotesize,
  language=C,
  numbers=left,
  extendedchars=true,
%  commentstyle=\color{olivegreen},
  title=\lstname,
  frame=single
}

\hypersetup{
  colorlinks=true,
  breaklinks=true,
  linkcolor=black,
  filecolor=black,      
  urlcolor=black,
  citecolor=black
}

\begin{document}

\begin{titlepage}

\vspace*{8cm}

\noindent\textbf{\Huge Embroidermodder}

\vspace{10pt}

\noindent\rule{\linewidth}{2pt}

\vspace{10pt}

\begin{flushright}
\Large
    Reference Manual

\normalsize
    The design, analysis and rationale of all Embroidermodder projects.

\embversion

\vspace{10pt}

\url{https://www.libembroidery.org}

\publicationdate
\end{flushright}

\vspace{6cm}

\begin{flushleft}
\Large
\emph{The Embroidermodder Team}

\url{embroidermodder@gmail.com}

\vspace{10pt}

\noindent\rule{\linewidth}{1pt}

\end{flushleft}
    
\end{titlepage}


\vspace*{8cm}

\begin{quote}
Copyright \copyright{} 2013-2023 The Embroidermodder Team.

\url{https://www.libembroidery.org}

The Embroidermodder Team consists of all contributors to our projects
at \url{https://github.com/Embroidermodder}. A copy of the contributor
list is in the Credits section below
and is maintained at \url{https://www.libembroidery.org/docs/credits}.

\bigskip

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.
A copy of the license is included in the section entitled ``GNU
Free Documentation License''.
\end{quote}

\newpage

\vspace*{8cm}

\begin{center}
    \emph{Dedicated to Jonathan Grieg}
    
    \vspace{1cm}
    
    \emph{Open source software is made by people who care about good tools
     and other people.}
    
    \vspace{1cm}
    
    \emph{You gave us so many ideas worth saving and we'll be working on,
    and sharing, your creations for some time.}
    
    \vspace{1cm}
    
    \emph{Rock on!}
\end{center}
    
\newpage

\tableofcontents

\chapter{Introduction}

\section{The Embroidermodder Project and Team}

The \emph{Embroidermodder 2} project is a collection of small software
utilities for manipulating, converting and creating embroidery files in all
major embroidery machine formats. The program *Embroidermodder 2* itself
is a larger graphical user interface (GUI) which is at the heart of the project.

The tools and associated documents are:

\begin{itemize}
\item The website https://www.libembroidery.org
\item This reference manual covering the development of all these projects with
the current version available here:
\url{https://www.libembroidery.org/embroidermodder_2.0_manual.pdf}
\if{0}
\item The GUI *Embroidermodder 2* covered in Chapter~\ref{GUI}.
\item The core library of low-level functions: `libembroidery`, covered in
Chapter~\ref{libembroidery}
\item The CLI `embroider`, which is part of libembroidery
\item Mobile embroidery format viewers and tools convered in Chapter~\ref{Mobile}.
\item Specs for an open source hardware embroidery machine extension called the
Portable Embroidery Tool (PET) which is also part of libembroidery.
See Chapter~\ref{PET}.
\fi
\end{itemize}

The website, this manual and some scripts to construct the distribution are
maintained in %\citep{thewebsite}.

They all tools to make the standard
user experience of working with an embroidery machine better without expensive
software which is locked to specific manufacturers and formats. But ultimately
we hope that the core *Embroidermodder 2* is a practical, ever-present tool in
larger workshops, small cottage industry workshops and personal hobbyist's
bedrooms.

Embroidermodder 2 is licensed under the zlib license and we aim to keep all of our tools open
source and free of charge. If you would like to support the project check out our  Open
Collective (https://opencollective.com/embroidermodder) group.
If you would like to help,
please join us on GitHub. This document is written as developer training as well helping new
users (see the last sections) so this is the place to learn how to start changing the code.

The Embroidermodder Team is the collection of people who've submitted
patches, artwork and documentation to our three projects.
The team was established by Jonathan Greig and Josh Varga.
The full list is actively maintained below.

\subsection{Core Development Team}

Embroidermodder 2:

\begin{itemize}
\item Jonathan Greig (\url{https://github.com/redteam316})
\item Josh Varga (\url{https://github.com/JoshVarga})
\item Robin Swift (\url{https://github.com/robin-swift})
\end{itemize}

Embroidermodder 1:

\begin{itemize}
\item Josh Varga (\url{https://github.com/JoshVarga})
\item Mark Pontius (\url{http://sourceforge.net/u/mpontius/profile})
\end{itemize}

\subsection{Credits for Embroidermodder 2, libembroidery and all other related code}

If you have contributed and wish to be added to this list, alter the  README on Embroidermodder
github page (https://github.com/Embroidermodder/Embroidermodder) and we'll copy it to the
libembroidery source code since that is credited to ``The Embroidermodder Team``.

\include{sections/credits.tex}

\section{History}

\subsection{Embroidermodder 1}

The Embroidermodder Team is also inspired by the original Embroidermodder that
was built by Mark Pontius and the same Josh Varga on SourceForge which
unfortunately appears to have died from linkrot. We may create a distribution
on here to be the official ``legacy`` Embroidermodder code but likely in a
seperate repository because it's GNU GPL v3 and this code is written to be
zlib (that is, permissive licensed) all the way down.

One reason why this is useful is that the rewrite by Jonathan Greig, John Varga
and Robin Swift for Embroidermodder 2 should have no regressions: no features
present in v1 should be missing in v2.

\section{Features}

Embroidermodder 2 has many advanced features that enable you to create awesome designs quicker, tweak existing designs to perfection, and can be fully customized to fit your workflow.

A summary of these features:

* Cross Platform
* Realistic rendering
* Various grid types and auto-adjusting rulers
* Many measurement tools
* Add text to any design
* Supports many formats
* Batch Conversion
* Scripting API

\section{Cross Platform}

If you use multiple operating systems, it's important to choose software that works on all of them.

Embroidermodder 2 runs on Windows, Linux and Mac OS X. Let's not forget the  Raspberry
Pi (https://www.raspberrypi.org).

.. image::
   images/features-platforms-1.png

\section{Realistic Rendering}

It is important to be able to visualize what a design will look like when stitched and our
pseudo ``3D`` realistic rendering helps achieve this
%(see Figure~\ref{real-render}).

Real render examples.

.. image::
   images/features-realrender-1.png

.. image::
   images/features-realrender-2.png

.. image::
   images/features-realrender-3.png

\subsection{Various grid types and auto-adjusting rulers}

Making use of the automatically adjusting ruler in conjunction with the grid will ensure your
design is properly sized and fits within your embroidery hoop area.

Use rectangular, circular or isometric grids to construct your masterpiece!

Multiple grids and rulers in action Figure ref fig grid-ruler.

Grid and ruler examples.

.. image::
   images/features-grid-ruler-1.png

\subsection{Many measurement tools}

Taking measurements is a critical part of creating great designs. Whether you are designing
mission critical embroidered space suits for NASA or some other far out design for your next
meet-up, you will have precise measurement tools at your command to make it happen. You can
locate individual points or find distances between any 2 points anywhere in the design!

Take quick and accurate measurements:

.. image::
   images/features-measure-1.png

\subsection{Add text to any design}

Need to make company apparel for all of your employees with individual names on them? No sweat.
Just simply add text to your existing design or create one from scratch, quickly and easily.
Didn't get it the right size or made a typo? No problem. Just select the text and update it
with the property editor.

Add text and adjust its properties quickly:

.. image::
   images/features-text-1.png

\subsection{Supports many formats}

Embroidery machines all accept different formats. There are so many formats
available that it can sometimes be confusing whether a design will work with your machine.

Embroidermodder 2 supports a wide variety of embroidery formats as well as several vector
formats, such as SVG and DXF. This allows you to worry less about which designs you can use.

\subsection{Batch Conversion}

Need to send a client several different formats? Just use libembroidery-convert, our command
line utility which supports batch file conversion.

There are a multitude of formats to choose from:

.. image::
   images/features-formats-1.png

\subsection{Scripting API}

If you've got programming skills and there is a feature that isn't currently available that you
absolutely cannot live without, you have the capability to create your own custom commands for
Embroidermodder 2. We provide an QtScript API which exposes various application functionality
so that it is possible to extend the application without requiring a new release. If you have
created a command that you think is worth including in the next release, just  contact
us (contact.html) and we will review it for functionality, bugs, and finally inclusion.

An Embroidermodder 2 command excerpt:

.. image::
   images/features-scripting-1.png

% scripting screenshot

\section{Scraps}

For
Embroidermodder 2.0.0-alpha4, libembroidery 1.0.0-alpha, PET 1.0.0-alpha
and EmbroideryMobile 1.0.0-alpha.

Since the document is shipped automatically try to update the revnumber each
time you edit using `revision.sh`.

Test these:

\begin{lstlisting}
sudo apt install latexml texlive-latex-base imagemagick info2man

# For our command line tools:
makeinfo embroider.texi -o embroider.info
info2man embroider.info > embroider.1
texi2pdf embroider.texi
# Or groff macro package for example ms.
# These may be housed in libembroidery since they're to be shipped as part of
# the embroider tarball.

# For online documentation:
pandoc embroidermodder_refman.tex -f latex -t html -s -o emb_refman.html --bibliography embroidermodder.bib
# Or latexml/latexmlpost
\end{lstlisting}

\subsection{Command Language}

Printer Command Language (PCL), see %\citet{packard1992pcl}.

HP-GL/2 Vector Graphics \index{HP-GL/2} described in %\citet{packard1992pcl}.
Has commands like: \texttt{PU} Pen Up, \texttt{PR} Plot Relative,
\texttt{EP} edge polygon.

So commands read like this:

\begin{lstlisting}
PA40,10;
\end{lstlisting}

command argument seperator (\texttt{,}) argument terminator(\texttt{;})

Constructing new commands from old ones in the command language is less
natural in the HP-GL/2 language, but a similar layer for us is
the tajima DST format (CITE) for existing printers and CNC commands for
direct control... where'd we'd use G-Code (CITE) and Linux CNC (CITE).

Could we `setpagedevice` to a printer in some cases and a similar CUPS service
for embroidery machines in others?

All systems are supported by ghostscript, when you account for homebrew (CITE):

\begin{lstlisting}
brew update
brew upgrade
brew install ghostscript
brew cleanup
\end{lstlisting}

Vector graphic logos don't require the SVG Qt library.

\subsection{Man Pages}

We maintain a traditional manpage for \texttt{embroider} using
the basic macros.

\subsection{Arduino}

\begin{lstlisting}
apt-get install avr-libc gcc-avr uisp avrdude
\end{lstlisting}

\chapter{Libembroidery}

(Under construction, please wait for v1.0 release.)

Libembroidery is a low-level library for reading, writing,
and altering digital embroidery files in C. It is part of the Embroidermodder Project
for open source machine embroidery.

Libembroidery is the underlying library that is used by Embroidermodder 2
and is developed by  The Embroidermodder Team %\ref{the-embroidermodder-team}.
A full list of contributors to the project is maintained in
the Embroidermodder 2 github (https://github.com/Embroidermodder/embroidermodder)
in the file ``CREDITS.md``. It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called ``embroider`` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

\subsection{Documentation}

Libembroidery is documented as part of this reference manual. If you need
libembroidery for any non-trivial usage or want to contribute to the library we
advise you read the appropriate design sections of the manual first. Copies of
this manual will be shipped with the packaged version of libembroidery, but to
build it we use the Doxyfile in
\url{https://github.com/Embroidermodder/embroidermodder} the Embroidermodder git
repository.

For more basic usage, `embroider` should have some in-built help
starting with:

\begin{lstlisting}
$ embroider --help
\end{lstlisting}

\subsection{License}

Libembroidery is distributed under the permissive zlib licence, see the LICENCE
file.

\section{Demos}

We're currently trying out some fill techniques which will be demonstrated here
and in the script \texttt{qa\_test.sh}.

\includegraphics[width=0.5\textwidth]{images/examples/logo.png}

Converts to:

\includegraphics[width=0.5\textwidth]{images/examples/crossstitch_logo.png}

\subsection{Build}

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:

%\lstinputlisting{examples/build_libembroidery.sh}

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

% \citep{packard1992pcl}
% \citep{linuxcncsrc}
% \citep{linuxcnc}
% \citep{adobe1990postscript}
% \citep{postscript1999postscript}
% \citep{eduTechDST}
% \citep{cups}
% \citep{millOperatorsManual}
% \citep{oberg1914machinery}
% \citep{dxf_reference}
% \citep{embroidermodder_source_code}
% \citep{libembroidery_source_code}
% \citep{acatina}
% \citep{kde_tajima}
% \citep{wotsit_archive}
% \citep{wotsit_siterip}
% \citep{fineemb_dst}
% \citep{edutechwiki_dst}

\section{Graphical User Interface for PC}
\label{GUI}

\subsection{Overview}

\emph{UNDER MAJOR RESTRUCTURING, PLEASE WAIT FOR VERSION 2}

Embroidermodder is a free machine embroidery application.
The newest version, Embroidermodder 2 can:

\begin{itemize}
\item edit and create embroidery designs
\item estimate the amount of thread and machine time needed to stitch a design
\item convert embroidery files to a variety of formats
\item upscale or downscale designs
\item run on Windows, Mac and Linux
\end{itemize}

\emph{Embroidermodder 2} is very much a work in progress since we're doing a ground
up rewrite to an interface in C using the GUI toolkit SDL2.
The reasoning for this is detailed in the issues tab.

For a more in-depth look at what we are developing read our
website (\url{https://www.libembroidery.org}) which includes these docs as well
as the up-to date printer-friendly versions. These discuss recent changes,
plans and has user and developer guides for all the Embroidermodder projects.

To see what we're focussing on right now, see the Open Collective
News (\url{https://opencollective.com/embroidermodder}).

// fixme
This current printer-friendly version
is here (\url{https://www.libembroidery.org/downloads/emrm.pdf}).

\subsection{License}

The source code is under the terms of the zlib license: see `LICENSE.md`
in the source code directory.

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.

%A copy of the license is included in Section~\ref{GNU-free-documentation-license}.

\subsection{Build and Install}

Assuming you already have the SDL2 libraries you can proceed to using the fast build, which
assumes you want to build and test locally.

The fast build should be:

\begin{verbatim}
bash build.sh
\end{verbatim}

or, on Windows:

\begin{verbatim}
.\build.bat
\end{verbatim}

Then run using the `run.bat` or `run.sh` scripts in the build/ directory.

Otherwise, follow the instructions below.

If you plan to install the dev version to your system (we recommend you wait
for the official installers and beta release first) then use the CMake build
instead.

\subsection{Install on Desktop}

We recommend that if you want to install the development version you use the CMake build. Like
this:

\begin{lstlisting}
git submodule --init --update

mkdir build
cd build
cmake ..
cmake --build .
sudo cmake --install .
\end{lstlisting}

These lines are written into the file:

\begin{lstlisting}
./build_install.sh
\end{lstlisting}

On Windows use the next section.

\section{History}

Embroidermodder 1 was started by Mark Pontius in 2004 while staying up all night
with his son in his first couple months. When Mark returned to his day job, he
lacked the time to continue the project. Mark made the decision to focus on his
family and work, and in 2005, Mark gave full control of the project to Josh
Varga so that Embroidermodder could continue its growth.

Embroidermodder 2 was conceived in mid 2011 when Jonathan Greig and Josh Varga
discussed the possibility of making a cross-platform version. It is currently in
active development and will run on GNU/Linux, Mac OS X, Microsoft Windows and
Raspberry Pi.

All Embroidermodder downloads (downloads.html) are hosted on SourceForge.

The source code for Embroidermodder 1
(\url{http://sourceforge.net/p/embroidermodder/code/HEAD/tree/embroidermodder1})
has always been hosted on Sourceforge.

The source code for Embroidermodder 2
(\url{https://github.com/Embroidermodder/Embroidermodder}) was moved to GitHub
on July 18, 2013.

The website for Embroidermodder
(\url{https://github.com/Embroidermodder/www.libembroidery.org}) was moved to
GitHub on September 9, 2013.

\section{Contact us}

For general questions email: \url{mailto:embroidermodder@gmail.com}.

To request a new feature  open an issue on the main Embroidermodder GitHub
repository (\url{https://github.com/Embroidermodder/Embroidermodder/issues}).
We'll move it to the correct repository.

\section{Downloads}

\subsection{Alpha Build}

This is a highly experimental build: we recommend users wait for the beta
release when the basic features are functional.

Visit our  GitHub Releases page
(\url{https://github.com/Embroidermodder/Embroidermodder/releases})
for the current build. Unfortunately, earlier builds went down with the
Sourceforge page we hosted them on.

\chapter{GUI}

Embroidermodder 2 is very much a work in progress since we're doing a ground
up rewrite to an interface in Python using the GUI toolkit Tk. The reasoning for
this is detailed in the issues tab.

For a more in-depth look at what we are developing read the developer notes (link to dev notes
section). This discusses recent changes in a less formal way than a changelog (since this
software is in development) and covers what we are about to try.

\section{Documentation}

The documentation is in the form of the website
(included in the `docs/` directory) and the printed docs in this file.

\subsection{Development}

If you wish to develop with us you can chat via the contact email on the
website (\url{https://www.libembroidery.org}) or in the issues tab on the
github page (\url{https://github.com/Embroidermodder/Embroidermodder/issues}).
People have been polite and friendly in these conversations and I (Robin) have
really enjoyed them. If we do have any arguments please note we have a Code of
Conduct (\texttt{CODE\_OF\_CONDUCT.md}) so there is a consistent policy to enforce when
dealing with these arguments.

The first thing you should try is building from source using the build advice(link to build)
above. Then read some of the development notes (link to dev notes.md) to get the general
layout of the source code and what we are currently planning.

\subsection{Testing}

To find unfixed errors run the tests by launching from the command line with:

\begin{lstlisting}
$ embroidermodder --test
\end{lstlisting}

then dig through the output. It's currently not worth reporting the errors, since
there are so many but if you can fix anything reported here you can submit a PR.

\section{Code Optimisations and Simplifications}

\subsection{Geometry-}

The geometry is stored, processed and altered via libembroidery. See the Python specific part
of the documentation for libembroidery for this. What the code in Embroidermodder does is make
the GUI widgets to change and view this information graphically.

For example if we create a circle with radius 10mm and center at `(20mm, 30mm)` then fill it
with stitches the commands would be

\lstinputlisting{examples/geometry.py}

but the user would do this through a series of GUI actions:

\begin{itemize}
\item Create new file
\item Click add circle
\item Use the Settings dialog to alter the radius and center
\item Use the fill tool on circle
\item Select satin from the drop down menu
\end{itemize}

So EM2 does the job of bridging that gap.

\subsection{Postscript Support}

In order to safely support user contributed/shared data that can define, for
example, double to double functions we need a consistent processor for these
descriptions.

Embroidermodder backends to the postscript interpreter included in libembroidery
to accomplish this.

For example the string: \texttt{5 2 t mul add} is equivalent to
the expression $2*t + 5$.

The benefit of not allowing this to simply be a Python expression is that it is safe against
malicious use, or accidental misuse. The program can identify whether the output is of the
appropriate form and give finitely many calculations before declaring the function to have run
too long (stopping equations that hang).

To see examples of this see the \texttt{assets/shapes/*.ps} files.

\subsection{SVG Icons}

To make the images easier to alter and restyle we could switch to svg icons.
There's some code in the git history to help with this.

\subsection{The Actions System}

In order to simplify the development of a GUI that is flexible and easy to
understand to new developers we have a custom action system that all user
actions will go via an \texttt{actuator} that takes a string argument. By using a
string argument the undo history is just an array of strings.

The C \texttt{action\_hash\_data} struct will contain: the icon used, the
labels for the menus and tooltips and the function pointer for that action.
There will be an accompanying argument for this function call, currently being
drafted as \texttt{action\_call}. So when the user makes a function call it should
contain information like the mouse position, whether special key is pressed etc.

\subsection{Accessibility}

Software can be more or less friendly to people with dyslexia, partial
sightedness, reduced mobility and those who don't speak English. Embroidermodder
2 has, in its design, the following features to help:

\begin{itemize}
\item icons for everything to reduce the amount of reading required
\item the system font is configurable: if you have a dyslexia-friendly font you
    can load it
\item the interface rescales to help with partial-sightedness
\item the system language is configurable, unfortunately the docs will only be
    in English but we can try to supply lots of images of the interface to make it
    easier to understand as a second language
\item buttons are remappable: XBox controllers are known for being good for
    people with reduced mobility so remapping the buttons to whatever setup you have
    should help
\end{itemize}

Note that most of these features will be released with version 2.1, which is planned for around
early 2023.

\subsection{Sample Files}

Various sample embroidery design files can be found in the
\texttt{embroidermodder2/samples} folder.

\subsection{Shortcuts}

A shortcut can be made up of zero or more modifier keys and at least one non-modifier key
pressed at once.

To make this list quickly assessable, we can produce a list of hashes which are simply the
flags ORed together.

The shortcuts are stored in the csv file `shortcuts.csv` as a 5-column table
with the first 4 columns describing the key combination. This is loaded into
the shortcuts `TABLE`. Each tick the program checks the input state for this
combination by first translating the key names into indices for the key state,
then checking for whether all of them are set to true.

\subsection{Removed Elements}

So I've had a few pieces of web infrastructure fail me recently and I think
it's worth noting. An issue that affects us is an issue that can effect people
who use our software.

\subsection{Qt and dependencies}

Downloading and installing Qt has been a pain for some users (46Gb on possibly
slow connections).

I'm switching to FreeGLUT 3 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

\subsection{Social Platform}

Github is giving me a server offline (500) error and is still giving a bad ping.

So... all the issues and project boards etc. being on Github is all well and
good assuming that we have our own copies. But we don't if Github goes down or
some other major player takes over the space and we have to move (again, since
this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between them.

\subsection{OpenGL}

OpenGL rendering within the application. This will allow for Realistic Visualization - Bump
Mapping/OpenGL/Gradients?

This should backend to a C renderer or something.

\subsection{Configuration Data Ideas}

Embroidermodder should boot from the command line regardless of whether it is or is not
installed (this helps with testing and running on machines without root). Therefore, it can
create an initiation file but it won't rely on its existence to boot:
\texttt{~/.embroidermodder/config.json}.

\begin{itemize}
\item Switch colors to be stored as 6 digit hexcodes with a `\#`.
\item We've got close to a hand implemented ini read/write setup in `settings.py`.
\end{itemize}

\subsection{Distribution}
\index{distribution}

When we release the new pip wheel we should also package:

\begin{itemize}
\item \texttt{.tar.gz} and \texttt{.zip} source archive.
\item Debian package
\item RPM package
\end{itemize}

Only do this once per minor version number.

.. todo::
   Screenshot a working draft to demonstrate.

\subsection{Perennial Jobs}

\begin{itemize}
\item Check for memory leaks
\item Clear compiler warnings on `-Wall -ansi -pedantic` for C.
\item Write new tests for new code.
\item Get Embroidermodder onto the current version of libembroidery.
\item PEP7 compliance.
\item Better documentation with more photos/screencaps.
\end{itemize}

\subsection{Full Test Suite}
\index{testing}

(This needs a hook from Embroidermodder to embroider's full test suite.)

The flag \texttt{--full-test-suite} runs all the tests that have been written.
Since this results in a lot of output the details are both to stdout
and to a text file called \texttt{test\_matrix.txt}.

Patches that strictly improve the results in the \texttt{test\_matrix.txt} over
the current version will likely be accepted and it'll be a good place
to go digging for contributions. (Note: strictly improve means that
the testing result for each test is as good a result, if not better.
Sacrificing one critera for another would require some design work
before we would consider it.)

\subsection{Symbols}
\index{symbols}

Symbols use the SVG path syntax.

In theory, we could combine the icons and symbols systems, since they could be
rendered once and stored as icons in Qt. (Or as textures in FreeGLUT.)

Also we want to render the patterns themselves using SVG syntax, so it would
save on repeated work overall.

\section{Features}

\subsection{Bindings}
\index{bindings}

Bindings for libembroidery are maintained for the languages we use internally
in the project, for other languages we consider that the responsibility of
other teams using the library.

So libembroidery is going to be supported on:

\begin{itemize}
\item \texttt{C} (by default)
\item \texttt{C++} (also by default)
\item \texttt{Java} (for the Android\index{Android} application MobileViewer)
\item \texttt{Swift} (for the iOS\index{iOS} application iMobileViewer)
\end{itemize}

For \texttt{C\#}\index{C\#}\index{C-sharp} we recommend directly calling the function directly
using the DllImport feature:

\begin{lstlisting}
/* Calling readCsv() via C# as a native function. */
[DllImport("libembroidery.so", EntryPoint="readCsv")]
\end{lstlisting}

see this StackOverflow discussion for help:
https://stackoverflow.com/questions/11425202/is-it-possible-to-call-a-c-function-from-c-net

For Python you can do the same using ctypes:
https://www.geeksforgeeks.org/how-to-call-a-c-function-in-python/

\subsection{Other Supported Thread Brands}
\index{supported threads}

The thread lists that aren't preprogrammed into formats but are indexed in
the data file for the purpose of conversion or fitting to images/graphics.

\begin{itemize}
\item Arc Polyester
\item Arc Rayon
\item Coats and Clark Rayon
\item Exquisite Polyester
\item Fufu Polyester
\item Fufu Rayon
\item Hemingworth Polyester
\item Isacord Polyester
\item Isafil Rayon
\item Marathon Polyester
\item Marathon Rayon
\item Madeira Polyester
\item Madeira Rayon
\item Metro Polyester
\item Pantone
\item Robison Anton Polyester
\item Robison Anton Rayon
\item Sigma Polyester
\item Sulky Rayon
\item ThreadArt Rayon
\item ThreadArt Polyester
\item ThreaDelight Polyester
\item Z102 Isacord Polyester
\end{itemize}

\section{House Style}

A basic set of guidelines to use when submitting code.

\subsection{Naming Conventions}

Name variables and functions intelligently to minimize the need for comments.
It should be immediately obvious what information it represents.
Short names such as x and y are fine when referring to coordinates.
Short names such as i and j are fine when doing loops.

Variable names should be \texttt{camelCase}, starting with a lowercase word followed by uppercase word(s).
C++ Class Names should be \texttt{CamelCase}, using all uppercase word(s).
C Functions that attempt to simulate namespacing, should be \texttt{"nameSpace\_camelCase"}.

All files and directories shall be lowercase and contain no spaces.

\subsection{Code Style}

Tabs should not be used when indenting. Setup your IDE or text editor to use 4 spaces.

If you use KATE (KDE Advanced Text Editor), modelines are included in our code to enforce 
some of our coding standards. When creating new C/C++ files, please add
the modeline to the bottom of the file followed by a blank line. Always make sure there
is an extra blank line at the end of a file.

When using braces, please put the brace on a new line, unless the code is specially formatted
for easier reading such as a block of one liner if/else statements.

Use exceptions sparingly.

if/else is preferred over switch/case.

Do not use ternary operator (?:) in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

\subsection{Version Control}

Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

\subsection{Comments}

When writing code, sometimes there are items that we know can be improved,
incomplete or need special clarification. In these cases, use the types of
comments shown below. They are pretty standard and are highlighted by many editors to
make reviewing code easier. We also use shell scripts to parse the code to find
all of these occurances so someone wanting to go on a bug hunt will be able to
easily see which areas of the code need more love.

libembroidery is written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

\begin{lstlisting}
/* C Style Comments */
/* TODO: This code clearly needs more work or further review. */
/* BUG: This code is definitely wrong. It needs fixed. */
/* HACK: This code shouldn't be written this way or I don't feel right about it. There may a better solution */
/* WARNING: Think twice (or more times) before changing this code. I put this here for a good reason. */
/* NOTE: This comment is much more important than lesser comments. */
\end{lstlisting}

These are rules for the general intended style of Embroidermodder's GUI source
code. Not included are anything that a compiler will warn you about: fixing
compiler warnings is more important than fixing style.

Most of this section is rationale, so skip to the end for the summary.

NEW DEVELOPERS: if your patch to Embroidermodder doesn't follow these rules,
don't worry about it. We only ask that your source code follow the basic rules
in the developer training section. These rules are for sculpting Embroidermodder
into a body of code that is resiliant to future bugs and reliable for users.

\subsection{Brevity}

Readable source code is short. Developers have finite time and becoming
acquainted with more than 1000 lines of dense C code is often too high a bar
for a new developer to a project. However, this leads to a bunch of tradeoffs
that have caused issues, so instead we consider the ``minimal library``
rather than ``minimal code`` approach. Not everyone will have used the more
abstract, syntactic features of C++ like templates and operator overloading.
Even if they are capable developers with these features it makes debugging far
harder since the choice of called function is interpreted by the compiler and compiler
errors are hundred line monsters per infraction of ``these are all of the possible
variations of this function that don't match``.

Using C++'s \texttt{unordered\_map} can simplify source code in that anything can
map to anything. However, it also means we don't have to associate related structures.
For example the \texttt{action\_table} came together replacing a collection of unordered maps
with one, then replaced the mapping with labelled indices. Since the ``actuator\_core``
is a giant switch/case statement this cuts the step of identifying the action by its
label `std::string`.
The structure given by this table allowed the code to be much
easier to interpret. So for this reason we don't recommend the use unordered maps or hashes any more.

\subsection{Rigidity Vs. Ease of Modification}

Difficult to restructure code is good if the structure that's there is good.
It guides new developers into safe practices without having to explain them.
Therefore we want ease of modification that comes from well chosen `structs`
and a carefully curated global header of .

\subsection{Developer Prose}

\subsection{Macro Policy}

Macros are great, you can do all sorts with them. But it's easy to make readable
short code that is really difficult to safely modify.

\subsection{Function Style}

\begin{enumerate}
\item Don't write a new convenience function unless there are two
existing applications of it in the source code.
\item .
\end{enumerate}

\subsection{Summary}

* .

\section{GUI Design}
\index{GUI}

Embroidermodder 2 was written in C++/Qt5 and it was far too complex. We had
issues with people not able to build from source because the Qt5 libraries were
so ungainly. So I decided to do a rewrite in C/SDL2 (originally FreeGLUT, but
that was a mistake) with data stored as YAML. This means linking 4-7 libraries
depending on your system which are all well supported and widely available.

This is going well, although it's slow progress as I'm trying to keep track of
the design while also doing a ground up rewrite. I don't want to throw away good
ideas. Since I also write code for libembroidery my time is divided.

Overview of the UI rewrite

(Problems to be solved in brackets.)

It's not much to look at because I'm trying to avoid using an external
widgets system, which in turn means writing things like toolbars and menubars
over. If you want to get the design the actuator is the heart of it.

Without Qt5 we need a way of assigning signals with actions, so this is what
I've got: the user interacts with a UI element, this sends an integer to the
actuator that does the thing using the current state of the mainwindow struct
of which we expect there to be exactly one instance. The action is taken out
by a jump table that calls the right function (most of which are missing in
action and not connected up properly). It also logs the number, along with
key parts of the main struct in the undo history (an unsolved problem because
we need to decide how much data to copy over per action). This means undo,
redo and repeat actions can refer to this data.

\chapter{To Do}

These should be sorted into relevant code sections.

\subsection{Current work}

\begin{itemize}
\item `EmbPattern *pattern` as a variable in the `View` class.
\item Removing the now unnecessary `SaveObject` class.
\item Converting all comments to C style.
\item Switching away from Doxygen-style in favour of direct commentary and a custom written reference manual.
\end{itemize}

\subsection{Documentation}

\begin{itemize}
\item Document all tests.
\item Automation of tests.
\item Ensure that the stitch count matches what we know the file has
\end{itemize}

\subsection{2.0 alpha1}

\begin{itemize}
\item WIP - Statistics from 1.0, needs histogram
\item WIP - Saving DST/PES/JEF (varga)
\item WIP - Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug
\end{itemize}

\subsection{2.0 alpha2}

\begin{itemize}
\item Notify user of data loss if not saving to an object format.
\item Import Raster Image
\item SNAP/ORTHO/POLAR
\item Layer Manager + LayerSwitcher DockWidget
\item Reading DXF
\end{itemize}

\subsection{2.0 alpha3}

\begin{itemize}
\item Writing DXF
\item Amount of Thread and Machine Time Estimation (also allow customizable times for setup, color changes, manually trimming jump threads, etc. that way a realistic total time can be estimated)
\item Otto Theme Icons - whatsthis icon doesn't scale well, needs redone
\item embroidermodder2.ico 16 x 16 looks horrible
\end{itemize}

\subsection{2.0 alpha4}

\begin{itemize}
\item WIP - CAD Command: Arc (rt)
\item Load/Save Menu/Toolbars configurations into settings.ini
\end{itemize}

\subsection{2.0 beta1}

\begin{itemize}
\item Custom Filter Bug - doesn't save changes in some cases
\item Cannot open file with \# in name when opening multiple files (works fine when opening the single file)
\item Closing Settings Dialog with the X in the window saves settings rather than discards them
\item WIP - Advanced Printing
\item Filling Algorithms (varga)
\item Otto Theme Icons - beta (rt) - Units, Render, Selectors
\end{itemize}

\subsection{2.0 rc1}

\begin{itemize}
\item Review KDE4 Thumbnailer
\item Documentation for libembroidery and formats
\item HTML Help files
\item Update language translations
\item CAD Command review: line
\item CAD Command review: circle
\item CAD Command review: rectangle
\item CAD Command review: polygon
\item CAD Command review: polyline
\item CAD Command review: point
\item CAD Command review: ellipse
\item CAD Command review: arc
\item CAD Command review: distance
\item CAD Command review: locatepoint
\item CAD Command review: move
\item CAD Command review: rgb
\item CAD Command review: rotate
\item CAD Command review: scale
\item CAD Command review: singlelinetext
\item CAD Command review: star
\item Clean up all compiler warning messages, right now theres plenty :P
\end{itemize}

\subsection{2.0 release}

\begin{itemize}
\item tar.gz archive
\item zip archive
\item Debian Package (rt)
\item NSIS Installer (rt)
\item Mac Bundle?
\item press release
\end{itemize}

\subsection{2.x/Ideas}

\begin{itemize}
\item libembroidery.mk for MXE project (refer to qt submodule packages for qmake based building. Also refer to plibc.mk for example of how write an update macro for github.)
\item libembroidery safeguard for all writers - check if the last stitch is an END stitch. If not, add an end stitch in the writer and modify the header data if necessary.
\item Cut/Copy - Allow Post-selection
\item CAD Command: Array
\item CAD Command: Offset
\item CAD Command: Extend
\item CAD Command: Trim
\item CAD Command: BreakAtPoint
\item CAD Command: Break2Points
\item CAD Command: Fillet
\item CAD Command: Chamfer
\item CAD Command: Split
\item CAD Command: Area
\item CAD Command: Time
\item CAD Command: PickAdd
\item CAD Command: Product
\item CAD Command: Program
\item CAD Command: ZoomFactor
\item CAD Command: GripHot
\item CAD Command: GripColor and GripCool
\item CAD Command: GripSize
\item CAD Command: Highlight
\item CAD Command: Units
\item CAD Command: Grid
\item CAD Command: Find
\item CAD Command: Divide
\item CAD Command: ZoomWindow (Move out of view.cpp)
\item Command: Web (Generates Spiderweb patterns)
\item Command: Guilloche (Generates Guilloche patterns)
\item Command: Celtic Knots
\item Command: Knotted Wreath
\item Lego Mindstorms NXT/EV3 ports and/or commands.
\item native function that flashes the command prompt to get users attention when using the
prompt is required for a command.
\item libembroidery-composer like app that combines multiple files into one.
\item Settings Dialog, it would be nice to have it notify you when switching tabs that a
setting has been changed. Adding an Apply button is what would make sense for this to happen.
\item Keyboard Zooming/Panning
\item G-Code format?
\item 3D Raised Embroidery
\item Gradient Filling Algorithms
\item Stitching Simulation
\item RPM packages?
\item Reports?
\item Record and Playback Commands
\item Settings option for reversing zoom scrolling direction
\item Qt GUI for libembroidery-convert
\item EPS format? Look at using Ghostscript as an optional add-on to libembroidery
\item optional compile option for including LGPL/GPL libs etc. with warning to user about license requirements.
\item Realistic Visualization - Bump Mapping/OpenGL/Gradients?
\item Stippling Fill
\item User Designed Custom Fill
\item Honeycomb Fill
\item Hilburt Curve Fill
\item Sierpinski Triangle fill
\item Circle Grid Fill
\item Spiral Fill
\item Offset Fill
\item Brick Fill
\item Trim jumps over a certain length.
\item FAQ about setting high number of jumps for more controlled trimming.
\item Minimum stitch length option. (Many machines also have this option too)
\item Add 'Design Details' functionality to libembroidery-convert
\item Add 'Batch convert many to one format' functionality to libembroidery-convert
\item EmbroideryFLOSS - Color picker that displays catalog numbers and names.
\item emscripten/javascript port of libembroidery
\end{itemize}

\subsection{Arduino}

\begin{itemize}
\item Fix emb-outline files
\item Fix thread-color files
\item Logging of Last Stitch Location to External USB Storage(commonly available and easily replaced), wait until TRE is available to avoid rework
\item inotool.org - seems like the logical solution for Nightly/CI builds
\item Smoothieboard experiments
\end{itemize}

\subsection{libembroidery-tests}

\begin{itemize}
\item looping test that reads 10 times while running valgrind. See ``embPattern\_loadExternalColorFile()`` Arduino leak note for more info.

\item todo sort todo list.
\item Alpha: High priority
  \item Statistics from 1.0, needs histogram
  \item Saving DST/PES/JEF (varga)
  \item Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug
\item Alpha: medium priority
  \item Notify user of data loss if not saving to an object format.
  \item Import Raster Image
  \item SNAP/ORTHO/POLAR
  \item Layer Manager + LayerSwitcher DockWidget
  \item Reading DXF
\item Alpha: low priority
  \item Writing DXF\item Up and Down keys cycle thru commands in the command prompt
  \item Amount of Thread, Machine Time Estimation (also allow customizable times for setup, color changes, manually trimming jump threads, etc...that way a realistic total time can be estimated)
  \item Otto Theme Icons - whatsthis icon doesn't scale well, needs redone
  \item embroidermodder2.ico 16 x 16 looks horrible
\item Alpha: lower priority
  \item CAD Command: Arc (rt)
\item beta
  \item Custom Filter Bug - doesn't save changes in some cases
  \item Cannot open file with `\#` in name when opening multiple files (works fine when opening the single file)
  \item Closing Settings Dialog with the X in the window saves settings rather than discards them
  \item Advanced Printing
  \item Filling Algorithms (varga)
  \item Otto Theme Icons - beta (rt) - Units, Render, Selectors
\item Finish before 2.0 release
  \item QDoc Comments
  \item Review KDE4 Thumbnailer
  \item Documentation for libembroidery and formats
  \item HTML Help files
  \item Update language translations
  \item CAD Command review: line
  \item CAD Command review: circle
  \item CAD Command review: rectangle
  \item CAD Command review: polygon
  \item CAD Command review: polyline
  \item CAD Command review: point
  \item CAD Command review: ellipse
  \item CAD Command review: arc
  \item CAD Command review: distance
  \item CAD Command review: locatepoint
  \item CAD Command review: move
  \item CAD Command review: rgb
  \item CAD Command review: rotate
  \item CAD Command review: scale
  \item CAD Command review: singlelinetext
  \item CAD Command review: star
  \item Clean up all compiler warning messages, right now theres plenty :P
\item 2.0
  \item tar.gz archive
  \item zip archive
  \item Debian Package (rt)
  \item NSIS Installer (rt)
  \item Mac Bundle?
  \item press release
\item 2.x/Ideas
  \item libembroidery.mk for MXE project (refer to qt submodule packages for qmake based building. Also refer to plibc.mk for example of how write an update macro for github.)
  \item libembroidery safeguard for all writers - check if the last stitch is an END stitch. If not, add an end stitch in the writer and modify the header data if necessary.
  \item Cut/Copy - Allow Post-selection
  \item CAD Command: Array
  \item CAD Command: Offset
  \item CAD Command: Extend
  \item CAD Command: Trim
  \item CAD Command: BreakAtPoint
  \item CAD Command: Break2Points
  \item CAD Command: Fillet
  \item CAD Command: Chamfer
  \item CAD Command: Split
  \item CAD Command: Area
  \item CAD Command: Time
  \item CAD Command: PickAdd
  \item CAD Command: Product
  \item CAD Command: Program
  \item CAD Command: ZoomFactor
  \item CAD Command: GripHot
  \item CAD Command: GripColor and GripCool
  \item CAD Command: GripSize
  \item CAD Command: Highlight
  \item CAD Command: Units
  \item CAD Command: Grid
  \item CAD Command: Find
  \item CAD Command: Divide
  \item CAD Command: ZoomWindow (Move out of view.cpp)
  \item Command: Web (Generates Spiderweb patterns)
  \item Command: Guilloche (Generates Guilloche patterns)
  \item Command: Celtic Knots
  \item Command: Knotted Wreath
  \item Lego Mindstorms NXT/EV3 ports and/or commands.
  \item native function that flashes the command prompt to get users attention when using the prompt is required for a command.
  \item libembroidery-composer like app that combines multiple files into one.
  \item Settings Dialog, it would be nice to have it notify you when switching tabs that a setting has been changed. Adding an Apply button is what would make sense for this to happen.
  \item Keyboard Zooming/Panning
  \item G-Code format?
  \item 3D Raised Embroidery
  \item Gradient Filling Algorithms
  \item Stitching Simulation
  \item RPM packages?
  \item Reports?
  \item Record and Playback Commands
  \item Settings option for reversing zoom scrolling direction
  \item Qt GUI for libembroidery-convert
  \item EPS format? Look at using Ghostscript as an optional add-on to libembroidery...
  \item optional compile option for including LGPL/GPL libs etc... with warning to user about license requirements.
  \item Realistic Visualization - Bump Mapping/OpenGL/Gradients?
  \item Stippling Fill
  \item User Designed Custom Fill
  \item Honeycomb Fill
  \item Hilbert Curve Fill
  \item Sierpinski Triangle fill
  \item Circle Grid Fill
  \item Spiral Fill
  \item Offset Fill
  \item Brick Fill
  \item Trim jumps over a certain length.
  \item FAQ about setting high number of jumps for more controlled trimming.
  \item Minimum stitch length option. (Many machines also have this option too)
  \item Add 'Design Details' functionality to libembroidery-convert
  \item Add 'Batch convert many to one format' functionality to libembroidery-convert
  \item EmbroideryFLOSS - Color picker that displays catalog numbers and names.
\item beta
  \item Realistic Visualization - Bump Mapping/OpenGL/Gradients?
  \item Get undo history widget back (BUG).
  \item Mac Bundle, .tar.gz and .zip source archive.
  \item NSIS installer for Windows, Debian package, RPM package
  \item GUI frontend for embroider features that aren't supported by embroidermodder: flag selector from a table
  \item Update all formats without color to check for edr or rgb files.
  \item Setting for reverse scrolling direction (for zoom, vertical pan)
  \item Keyboard zooming, panning
  \item New embroidermodder2.ico 16x16 logo that looks good at that scale.
  \item Saving dst, pes, jef.
  \item Settings dialog: notify when the user is switching tabs that the setting has been changed, adding apply button is what would make sense for this to happen.
  \item Update language translations.
  \item Replace KDE4 thumbnailer.
  \item Import raster image.
  \item Statistics from 1.0, needs histogram.
  \item SNAP/ORTHO/POLAR.
  \item Cut/copy allow post-selection.
  \item Layout into config.
  \item Notify user of data loss if not saving to an object format.
  \item Add which formats to work with to preferences.
  \item Cannot open file with `\#` in the name when opening multiple files but works with opening a single file.
  \item Closing settings dialog with the X in the window saves settings rather than discarding them.
  \item Otto theme icons: units, render, selectors, what's this icon doesn't scale.
  \item Layer manager and Layer switcher dock widget.
  \item Test that all formats read data in correct scale (format details should match other programs).
  \item Custom filter bug -- doesn't save changes in some cases.
  \item Tools to find common problems in the source code and suggest fixes to the developers. For example, a translation miss: that is, for any language other than English a missing entry in the translation table should supply a clear warning to developers.
  \item Converting Qt C++ version to native GUI C throughout.
  \item OpenGL Rendering: `Real` rendering to see what the embroidery looks like, Icons and toolbars, Menu bar.
  \item Libembroidery interfacing: get all classes to use the proper libembroidery types within them. So `Ellipse` has `EmbEllipse` as public data within it.
  \item Move calculations of rotation and scaling into `EmbVector` calls.
  \item GUI frontend for embroider features that aren't supported by embroidermodder: flag selector from a table
  \item Update all formats without color to check for edr or rgb files.
  \item Setting for reverse scrolling direction (for zoom, vertical pan)
  \item Keyboard zooming, panning
  \item Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
  \item New embroidermodder2.ico 16x16 logo that looks good at that scale.
  \item Settings dialog: notify when the user is switching tabs that the setting has been changed, adding apply button is what would make sense for this to happen.
\end{itemize}

\chapter{Introduction}

The \emph{Embroidermodder 2} project is a collection of small software utilities for
manipulating, converting and creating embroidery files in all major embroidery
machine formats. The program \textit{Embroidermodder 2} itself is a larger graphical
user interface (GUI) which is at the heart of the project.

This manual, the website (`embroidermodder.org`), mobile embroidery format viewers
and tools (`iMobileViewer`, `MobileViewer`), the core library of functions
(`libembroidery`) and CLI (`embroider`) are all tools to make the standard
user experience of working with an embroidery machine better without expensive
software which is locked to specific manufacturers and formats. But ultimately
we hope that the core \textit{Embroidermodder 2} is a practical, ever-present tool in
larger workshops, small cottage industry workshops and personal hobbyist's
bedrooms.

Embroidermodder 2 is licensed under the zlib license and we aim to keep all of
our tools open source and free of charge. If you would like to support the
project check out our Open Collective group. If you would like to help, please
join us on GitHub. This document is written as developer training as well
helping new users (see the last sections) so this is the place to learn how
to start changing the code.

\chapter{The Graphical User Interface: Embroidermodder 2.0.0-alpha}

\section{Overview}

\section{Features}

Embroidermodder 2 has many advanced features that enable you to create awesome designs quicker, tweak existing designs to perfection, and can be fully customized to fit your workflow.

A summary of these features:

\begin{itemize}
\item Cross Platform
\item Realistic rendering
\item Various grid types and auto-adjusting rulers
\item Many measurement tools
\item Add text to any design
\item Supports many formats
\item Batch Conversion
\item Scripting API
\end{itemize}

\subsection{Cross Platform}

If you use multiple operating systems, it's important to choose software that works on all of them.

Embroidermodder 2 runs on Windows, Linux and Mac OS X. Let's not forget the Raspberry Pi (http://www.raspberrypi.org).

.. image::
   images/features-platforms-1.png

\subsection{Realistic Rendering}

It is important to be able to visualize what a design will look like when stitched and our pseudo ``3D`` realistic rendering helps achieve this.

Realistic rendering sample \#1:

.. image::
   images/features-realrender-1.png

Realistic rendering sample \#2:

.. image::
   images/features-realrender-2.png

Realistic rendering sample \#3:

.. image::
   images/features-realrender-3.png

Various grid types and auto-adjusting rulers

Making use of the automatically adjusting ruler in conjunction with the grid will ensure your design is properly sized and fits within your embroidery hoop area.

Use rectangular, circular or isometric grids to construct your masterpiece!

Multiple grids and rulers in action:

.. image::
   images/features-grid-ruler-1.png

\subsection{Many measurement tools}

Taking measurements is a critical part of creating great designs. Whether you are designing mission critical embroidered space suits for NASA or some other far out design for your next meet-up, you will have precise measurement tools at your command to make it happen. You can locate individual points or find distances between any 2 points anywhere in the design!

Take quick and accurate measurements:

.. image::
   images/features-measure-1.png

\subsection{Add text to any design}

Need to make company apparel for all of your employees with individual names on them? No sweat. Just simply add text to your existing design or create one from scratch, quickly and easily.
Didn't get it the right size or made a typo? No problem. Just select the text and update it with the property editor.

Add text and adjust its properties quickly:

.. image::
   images/features-text-1.png

\subsection{Supports many formats}

Embroidery machines all accept different formats. There are so many formats available that it can sometimes be confusing whether a design will work with your machine.

Embroidermodder 2 supports a wide variety of embroidery formats as well as several vector formats, such as SVG and DXF. This allows you to worry less about which designs you can use.

\subsection{Batch Conversion}

Need to send a client several different formats? Just use libembroidery-convert, our command line utility which supports batch file conversion.

There are a multitude of formats to choose from:

.. image::
   images/features-formats-1.png

\subsection{Scripting API}

If you've got programming skills and there is a feature that isn't currently available that you absolutely cannot live without, you have the capability to create your own custom commands for Embroidermodder 2. We provide an QtScript API which exposes various application functionality so that it is possible to extend the application without requiring a new release. If you have created a command that you think is worth including in the next release, just <a href=``contact.html``>contact us</a> and we will review it for functionality, bugs, and finally inclusion.

An Embroidermodder 2 command excerpt:

.. image::
   images/features-scripting-1.png

\section{Contributing}

\subsection{Version Control}

Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

See the coding style ref (coding-style)

\section{Introduction}

\subsection{Basic Features}

\subsection{Move a single stitch in an existing pattern}

\begin{enumerate}
\item In the `File' menu, click `Open...'. When the open dialog appears find
 and select your file by double clicking the name of the file. Alternatively,
 left click the file once then click the `Open` button.
\item
\item In the `File' menu
\end{enumerate}

.. tip::
   For users who prefer

\subsection{Convert one pattern to another format}

\begin{enumerate}
1. In the `File` menu, click `Open...`.
2. The 
3. In the dropdown menu within the save dialog select the 
\end{enumerate}

\section{Advanced Features}

\section{Other Projects}

\subsection{Planning}

To see what's planned open the [Projects](https://github.com/Embroidermodder/Embroidermodder/projects/1) tab which sorts all of the GitHub Issues into columns.

\subsection{Format Support}

Support for Singer FHE, CHE (Compucon) formats?

\subsection{Embroidermodder Project Coding Standards}

A basic set of guidelines to use when submitting code.

\subsection{Naming Conventions}

Name variables and functions intelligently to minimize the need for comments.
It should be immediately obvious what information it represents.
Short names such as ``x`` and ``y`` are fine when referring to coordinates.
Short names such as ``i`` and ``j`` are fine when doing loops.

Variable names should be `camelCase`, starting with a lowercase word followed by uppercase word(s).
C Functions that attempt to simulate namespacing, should be `nameSpace\_camelCase`.

All files and directories shall be lowercase and contain no spaces.

\subsection{Code Style}

Tabs should not be used when indenting. Setup your IDE or text editor to use 4 spaces.

\subsection{Braces}

For functions: please put each brace on a new line.

\begin{lstlisting}
void
function_definition(int argument)
{
    /* code block */
}
\end{lstlisting}

For control statements: please put the first brace on the same line.

\begin{lstlisting}
if (condition) {
    /* code block */    
}
\end{lstlisting}

Use exceptions sparingly.

Do not use ternary operator `(?:)` in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

\subsection{Version Control}

Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

\subsection{Comments}

When writing code, sometimes there are items that we know can be improved,
incomplete or need special clarification. In these cases, use the types of
comments shown below. They are pretty standard and are highlighted by many editors to
make reviewing code easier. We also use shell scripts to parse the code to find
all of these occurrences so someone wanting to go on a bug hunt will be able to
easily see which areas of the code need more love. Use the same convention
as libembroidery.

libembroidery is written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

\begin{lstlisting}
/* C Style Comments */
/* TODO: This code clearly needs more work or further review. */
/* BUG: This code is definitely wrong. It needs fixed. */
/* HACK: This code shouldn't be written this way or I don't feel
* right about it. There may a better solution */
/* WARNING: Think twice (or more times) before changing this code.
* I put this here for a good reason. */
/* NOTE: This comment is much more important than lesser comments. */
\end{lstlisting}

\subsection{Donations}

Creating software that interfaces with hardware is costly. A summary
of some of the costs involved:

\begin{enumerate}
\item Developer time for 2 core developers
\item Computer equipment and parts
\item Embroidery machinery
\item Various electronics for kitbashing Embroiderbot
\item Consumable materials (thread, fabric, stabilizer, etc...)
\end{enumerate}

If you have found our software useful, please consider funding further
development by donating to the project on Open Collective
(https://opencollective.com/embroidermodder).

\section{Introduction}

\emph{(UNDER MAJOR RESTRUCTURING, PLEASE WAIT FOR VERSION 2.)}

Embroidermodder is a free machine embroidery application.
The newest version, Embroidermodder 2 can:

\begin{itemize}
\item edit and create embroidery designs
\item estimate the amount of thread and machine time needed to stitch a design
\item convert embroidery files to a variety of formats
\item upscale or downscale designs
\item run on Windows, Mac and Linux
\end{itemize}

For more information, see our website (\url{https://www.libembroidery.org})).

Embroidermodder 2 is very much a work in progress since we're doing a ground up
rewrite to an interface in Python using the GUI toolkit Tk. The reasoning for
this is detailed in the issues tab.

For a more in-depth look at what we are developing read the developer notes
\footnote{link to dev notes section}. This discusses recent changes in a less
formal way than a changelog (since this software is in development) and covers
what we are about to try.

To see what we're focussing on at the moment check this table.

.. table:: Plan

\begin{lstlisting}
|           *Date* +                                    *Event* |
+==================+============================================+
| April-June 2022  | Finish the conversion to C/SDL2            |

| July-August 2022 | Finish all the targets in the Design, or   |
|                  | assign them to 2.1.                        |

| September 2022   | Bugfixing, Testing, QA. libembroidery 1.0  |
|                  | will be released, then updates will slow   |
|                  | down and the Embroidermodder 2 development |
|                  | version will be fixed to the API of this   |
|                  | version.                                   |

| October 2022     | Embroidermodder 2 is officially released.  |
\end{lstlisting}

\section{Build and Install}

\subsection{Desktop}

First you must install the dependencies which aren't compiled into the source:

\begin{itemize}
\item \texttt{git}
\item \texttt{cmake}
\item A C compiler (we recommend \texttt{gcc} or \texttt{clang})
\end{itemize}

on Debian Linux/GNU use:

\begin{lstlisting}
$ sudo apt install git clang build-essential libsdl2-dev \
 libsdl2-images-dev libsdl2-ttf-dev
\end{lstlisting}

If you can't find a good fit for your system (on Windows use the section below),
try compiling the included submodules with:

\begin{lstlisting}
$ bash build_deps.sh
\end{lstlisting}

From here, on most sytems the command:

\begin{lstlisting}
$ bash build.sh
\end{lstlisting}

will build the software. Currently this is the 2.0-alpha, which will have a build code of
some kind.

\subsection{Dependencies and Build}

\subsection{Plans}

\subsection{Windows Specific Advice}

This is one of many possible ways to build the software on Windows,
this section is to help people who've not got a build environment to start with.

\begin{enumerate}
\item Download and install MSYS2 (follow their instructions): https://www.msys2.org/
\item Boot ``Mintty`` from the Start menu.
\item Use the commands:
\end{enumerate}

.. literalinclude:: build\_em\_on\_windows.sh
   :language: bash
   :encoding: latin-1
   :linenos:

\subsection{Mobile}

These are currently unsupported (see iMobileViewer and Mobileviewer for
iOS and Android respectively), but after the Desktop version is
released we'll work on them.

The Mobile version will share some of the UI and all of the backend,
so development of the Desktop version will help us make both.

\subsection{Documentation}

The documentation is in the form of the website (included in the `docs/`
directory) and the printed docs in this file.

\subsection{Development}

If you wish to develop with us you can chat via the contact email
on the website (https://www.libembroidery.org) or in the issues tab on the
github page (https://github.com/Embroidermodder/Embroidermodder/issues).
People have been polite and friendly in these conversations and I (Robin)
have really enjoyed them.
If we do have any arguments please note we have a
[Code of Conduct](CODE\_OF\_CONDUCT.md) so there is a consistent policy to
enforce when dealing with these arguments.

The first thing you should try is building from source using the [build advice](link to build)
above. Then read some of the [development notes](link to dev notes.md) to get the general
layout of the source code and what we are currently planning.


\section{Overall Structure}

\section{Code Optimisations and Simplifications}

\subsection{Current}

What Robin is currently doing.

Getting the code to pass PyLint, that involves getting all source files
under 1000 lines, renaming all variables to be in snake case.

Changing the seperation of code between EM and libembroidery.

Translating the Qt widget framework to Tk.

\subsection{Geometry}

The geometry is stored, processed and altered via libembroidery. See the Python
specific part of the documentation for libembroidery for this. What the code in
Embroidermodder does is make the GUI widgets to change and view this information
graphically.

For example if we create a circle with radius 10mm and center at (20mm, 30mm)
then fill it with stitches the commands would be

\begin{lstlisting}
from libembroidery import Pattern, Circle, Vector, satin
circle = Circle(Vector(20, 30), 10)
pattern = Pattern()
pattern.add_circle(circle, fill=satin)
pattern.to_stitches()
\end{lstlisting}

but the user would do this through a series of GUI actions:

1. Create new file
2. Click add circle
3. Use the Settings dialog to alter the radius and center
4. Use the fill tool on circle
5. Select satin from the drop down menu

So EM2 does the job of bridging that gap.

\section{Settings Dialog}

There are many codeblocks for changing out the colors in one go, for example:

\begin{lstlisting}
    self.mw.update_all_view_select_box_colors(    self.accept["display_selectbox_left_color"],
    self.accept["display_selectbox_left_fill"],
    self.accept["display_selectbox_right_color"],
    self.accept["display_selectbox_right_fill"],
    self.preview["display_selectbox_alpha"])
\end{lstlisting}

This could be replaced with a simpler call

\begin{lstlisting}
    self.mw.update_all_view_select_box_colors(
    self.accept["display_selectbox_colors"],
    self.preview["display_selectbox_alpha"])
\end{lstlisting}

where we require that

\begin{lstlisting}
    self.accept["display_selectbox_colors"] == {
    "left_color": "#color",
    "left_fill": "#color",
    "right_color": "#color",
    "right_fill": "#color"
    }
\end{lstlisting}

with `\#color` being some valid hex code.

\subsection{Kivy}

Once the tkinter interface is up and running we can experiment
with different frontends to improve the look of the application.
For example, the MIT licensed KIVY would allow us to replace the 
mobile development in Swift and Java with all Python development:

\url{https://kivy.org/#home}

\subsection{Data/Code Seperation}

All the "data" is in code files that are within the `config/`
submodule. So this way we don't have to deal with awkward data
packaging, it's just available as a single JSON style object
called `settings` available with this import line:

    from embroidermodder.config import settings

In order to pass PyLint style guides this will be split up and
formatted into Python code but no processing beyond inlining
the data into a single dict should be carried out here.

\subsection{The Settings Dictionary}

No more than 4 levels of indentation

Only strings, arrays, dicts and integers so matching the JSON standard. Ideally you should be able to copy/paste the data in and out and it would parse as JSON. Currently this fails because we have multi-line strings in Python syntax and inlining.

We may be able to extend the lisp support, which would deal with this. Or we can change multiline strings out for arrays of strings.

\subsection{Lisp Expression Support}

In order to safely support user contributed/shared data that can
define, for example, double to double functions we need a consistent
processor for these descriptions.

Embroidermodder uses a list processor (a subset of the language
Lisp which is short for LISt Processor) to accomplish this.

For example the string: \texttt{(+ (* t 2) 5)}.
is equivalent to the expression: $2*t + 5$.

The benefit of not allowing this to simply be a Python expression
is that it is safe against malicious use, or accidental misuse.
The program can identify whether the output is of the appropriate
form and give finitely many calculations before declaring the
function to have run too long (stopping equations that hang).

To see examples of this see \texttt{parser.py} and
\texttt{config/design\_primatives.py}.

It's also worth noting that we don't use the simpler reverse Polish
notation (RPN) approach because:

\begin{itemize}
\item It's more compact to use Lisp because `a b c + +` for example needs a new `+` sign for each new term as opposed to `(+ a b c)`.
\item It's easier to support expressions that are themselves function calls defined by the user (by adding support for `defun` or `lambda`.
\end{itemize}

\subsection{SVG Icons}

To make the images easier to alter and restyle we could
switch to svg icons. There's some code in the git history
to help with this.

\subsection{The Actions System}

In order to simplify the development of a GUI that is flexible and
easy to understand to new developers we have a custom action system that all
user actions will go via an `actuator` that takes a string argument. By using a
string argument the undo history is just an array of strings.

The C \texttt{action\_hash\_data} struct will contain: the icon used, the labels for the
menus and tooltips and the function pointer for that action.
There will be an accompanying argument for this function call, currently being
drafted as \texttt{action\_call}. So when the user makes a function call it should
contain information like the mouse position, whether special key is pressed
etc.

\subsection{Accessibility}

Software can be more or less friendly to people with dylexia, partial sightedness,
reduced mobility and those who don't speak English.
Embroidermodder 2 has, in its design, the following features to help:

\begin{itemize}
\item icons for everything to reduce the amount of reading required
\item the system font is configurable: if you have a dyslexia-friendly font you can load it
\item the interface rescales to help with partial-sightedness
\item the system language is configurable, unfortunately the docs will only be in English but we can try to supply lots of images of the interface to make it easier to understand as a second language
\item buttons are remappable: XBox controllers are known for being good for people with reduced mobility so remapping the buttons to whatever setup you have should help
\end{itemize}

Note that most of these features will be released with version 2.1, which is planned for around early 2023.

\subsection{Current Work}

* Converting C++ to Python throughout.
* OpenGL Rendering
  * ``Real`` rendering to see what the embroidery looks like.
  * Icons and toolbars.
  * Menu bar
* Libembroidery interfacing:
  * Get all classes to use the proper libembroidery types within them. So `Ellipse` has `EmbEllipse` as public data within it.
* Move calculations of rotation and scaling into `EmbVector` calls.
* Get undo history widget back (BUG).
* Switch website to a CMake build.
* GUI frontend for embroider features that aren't supported by embroidermodder: flag selector from a table
* Update all formats without color to check for edr or rgb files.
* EmbroideryFLOSS - Color picker that displays catalog numbers and names
* Setting for reverse scrolling direction (for zoom, vertical pan)
* Stitching simulation
* User designed custom fill
* Keyboard zooming, panning
* Advanced printing
* Libembroidery 1.0
* Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
* New embroidermodder2.ico 16x16 logo that looks good at that scale.
* saving dst, pes, jef
* Settings dialog: notify when the user is switching tabs that the setting has been changed, adding apply button is what would make sense for this to happen.
* Update language translations
* Replace KDE4 thumbnailer.
* Import raster image
* Statistics from 1.0, needs histogram.
* SNAP/ORTHO/POLAR
* Cut/copy allow post-selection
* Layout into config
* Notify user of data loss if not saving to an object format.
* Add which formats to work with to preferences.
* Cannot open file with \# in the name when opening multiple files but works with opening a single file.
* Closing settings dialog with the X in the window saves settings rather than discarding them.
* Otto theme icons: units, render, selectors, what's this icon doesn't scale
* Layer manager and Layer switcher dock widget
* test that all formats read data in correct scale (format details should match other programs).
* Custom filter bug -- doesn't save changes in some cases.
* Get flake8, pylint and tests to pass.
* Sphinx documentation from docstrings or similar.

For more details read on into the Design section.

\subsection{Sample Files}

Various sample embroidery design files can be found in the embroidermodder2/samples folder.

\subsection{Design}

These are key bits of reasoning behind why the software is built the way it is.

\subsection{CAD command review}

%cad_desc.csv


\subsection{Removed Elements}

So I've had a few pieces of web infrastructure fail me recently and
I think it's worth noting. An issue that affects us is an issue that
can effect people who use our software.

\subsection{Qt and dependencies}

Downloading and installing Qt has been a pain for some users
(46Gb on possibly slow connections).

I'm switching to FreeGLUT 3 (which is a whole other conversation) which means we
can ship it with the source code package meaning only a basic build
environment is necessary to build it.

\subsection{Social Platform}

Github is giving me a server offline (500) error and is still giving a bad ping.

So... all the issues and project boards etc. being on Github is all well and good assuming that we have our own copies. But we don't if Github goes down or some other major player takes over the space and we have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between them.

\subsection{Pandoc Documentation}

The documentation is, well better in that it's housed in the main repository,
but I'm not a fan of the ``write once build many`` approach as it means
trying to weigh up how 3 versions are going to render.

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive) one
per project.

\subsection{OpenGL}

OpenGL rendering within the application. This will allow for
Realistic Visualization - Bump Mapping/OpenGL/Gradients?

This should backend to a C renderer or something.

\subsection{Configuration Data Ideas}

embroidermodder should boot from the command line
regardless of whether it is or is not installed (this helps with testing and
running on machines without root). Therefore, it can create an initiation file
but it won't rely on its existence to boot: `~/.embroidermodder/config.json`.

* Switch colors to be stored as 6 digit hexcodes with a \texttt{\#}.
* We've got close to a hand implemented ini read/write setup in `settings.py`.

\subsection{Distribution}

When we release the new pip wheel we should also package:

* `.tar.gz` and `.zip` source archive.
* Debian package
* RPM package

Only do this once per minor version number.

\subsection{Scripting Overhaul}

Originally Embroidermodder had a terminal widget, this is why we removed it.

\begin{verbatim}
> ROBIN: I think supporting scripting within Embroidermodder doesn't make sense.
> 
> All features that use scripting can be part of libembroidery instead.
> Users who are capable of using scripting won't need it, they can alter their embroidery files in CSV format, or import pyembroidery to get access.
> It makes maintaining the code a lot more complicated, especially if we move away from Qt.
> Users who don't want the scripting feature will likely be confused by it, since we say that's what libembroidery, embroider and pyembroidery are for.
> 
> How about a simpler ``call user shell`` feature? Similar to texmaker we just call system on a batch or shell script supplied by the user and it processes the file directly then the software reloads the file. Then we aren't parsing it directly.
> 
> I don't want to change this without Josh's support because it's a fairly major change.
>
> JOSH: I totally agree.
> 
> I like the idea of scripting just so people that know how to code could write their own designs without needing to fully build the app. Scripting would be a very advanced feature that most users would be confused by. Libembroidery would be a good fit for advanced features.
> 
> Now we are using Python (again, sort of) this would be a lot more natural,
> perhaps we could boot the software without blocking the shell so they can
> interact? TODO: Screenshot a working draft to demonstrate.
\end{verbatim}

\subsection{Perennial Jobs}

\begin{itemize}
\item Check for memory leaks
\item Write new tests for new code.
\item Get Embroidermodder onto the current version of libembroidery.
\item PEP7 compliance.
\item Better documentation with more photos/screencaps.
\end{itemize}

\subsection{Developing for Android}

\url{https://developer.android.com/studio/projects/add-native-code}

\begin{lstlisting}
$ apt install google-android-ndk-installer cmake lldb gradle
\end{lstlisting}

\subsection{The Command Line Interface: `embroider`}

\subsection{Usage}

For basic use, we recommend you build as above, then run without arguments:

\begin{lstlisting}
$ embroider
\end{lstlisting}

which will print out this advice on how to use these tools without digging straight into the rest of this manual.

%.. literalinclude:: help_msg.txt

For each of the flags described here we will go into greater detail in this manual.

\subsection{To Flag}

\subsection{Circle Flag}

\subsection{Ellipse Flag}

\subsection{Line Flag}

\subsection{Polyline Flag}

\subsection{Polygon Flag}

\subsection{Satin Flag}

\subsection{Stitch Flag}

\subsection{Basic Test Suite}

The flag `--test` runs the tests that take the least time and have the most utility. If you're submitting a patch for review, please run:

\begin{lstlisting}
$ embroider --test | tail -n 1
\end{lstlisting}

You'll be presented with an overall PASS or FAIL for your build,
if your build fails you can try and trace the error with:

\begin{lstlisting}
$ valgrind embroider --verbose --test
\end{lstlisting}

or

\begin{lstlisting}
$ gdb --args embroider --verbose --test
\end{lstlisting}

depending on your preferred debugging approach. Passing this test
will be required for us to accept your patch.

\subsection{Full Test Suite}

The flag `--full-test-suite` runs all the tests that have been written.
Since this results in a lot of output the details are both to stdout
and to a text file called `test\_matrix.txt`.

Patches that strictly improve the results in the `test\_matrix.txt` over
the current version will likely be accepted and it'll be a good place
to go digging for contributions. (Note: strictly improve means that
the testing result for each test is as good a result, if not better.
Sacrificing one critera for another would require some design work
before we would consider it.)

\subsection{Ideas}

\subsection{Rendering system}

There are two forms of render that will be produced.

1. A raster format as ppm so we can have a pixel for pixel output (for example extracting the embedded images in some formats).
2. The SVG format that will be fairly similar to InkStitch's format.

We have an EmbImage struct to store the raster format.

\begin{lstlisting}
$ embroider test01.csv --render
\end{lstlisting}

currently creates a blank image. Previously the Hilbert curve test managed to
create a correctly rendered version.

\subsubsection{Tactile art and braille support}

One application I'd like to leave a reminder here for is automating embroidery
for blind and partially sighted people.

There are many limitations to making braille (cost, poor support, lack of
widespread adoption in the sighted world) and as such there is a strong DIY
culture around it.

There are blind internet users who can also run terminal applications using a
refreshable braille display, so in theory we could support an application like
this for them:

\begin{lstlisting}
$ embroider --braille ``Hello, world!`` hello.dst
\end{lstlisting}

which would produce braille that would read `Hello, world!` as an embroidery design.

Another option is tactile fills that use the same fill algorithms but are
designed better to facilitate tactile art.

I think the way forward on this is to call up the RNIB business advice line and ask for assistance once we have a working model. That way they can get us in contact with experts to review how legible the output is and usable the software is for the intended audience.

This is less important than getting better machine support but given the high social impact I think it should be a priority.

\subsection{The Low Level API: Libembroidery 1.0.0-alpha}


\subsection{API Reference}

\subsection{`convert`}


\subsection{Mobile Support: MobileViewer and iMobileViewer}

\subsection{Embroidermodder 2.0.0-alpha User Manual}

\subsection{Introduction}

\subsection{Basic Features}

\subsection{Move a single stitch in an existing pattern}

1. In the `File` menu, click `Open...`. When the open dialog appears find and select your file by double clicking the name of the file. Alternatively, left click the file once then click the `Open` button.
2. 
3. In the `File` menu

TIP: For users who prefer

\subsection{Convert one pattern to another}

1. In the `File` menu, click `Open...`.
2.  The
3.  In the dropdown menu within the save dialog select the

\subsection{Advanced Features}

\subsection{Other Projects}

\subsection{References}

\subsection{Ideas}

\subsection{Why this document}

I've been trying to make this document indirectly through the Github
issues page and the website we're building but I think a
straightforward, plain-text file needs to be the ultimate backup for
this. Then I can have a printout while I'm working on the project.

\subsection{Issues}

\subsection{Fix before Version 2}

So I've had a few pieces of web infrastructure fail me recently and I
think it's worth noting. An issue that affects us is an issue that can
effect people who use our software.

\begin{enumerate}
\item Googletests require a web connection to update and they update on each compilation.
\item Downloading and installing Qt has been a pain for some users (46Gb on possibly slow connections). I think it was davieboy64?
\item The documentation is, well better in that it's housed in the main repository, but I'm not a fan of the ``write once build many`` approach as it means trying to weigh up how 3 versions are going to render.
\item Github is giving me a server offline (500) error and is still giving a bad ping.
\item OpenGL rendering within the application. This will allow for Realistic Visualization - Bump Mapping/OpenGL/Gradients?
\item JSON configuration (Started, see \texttt{head -n 50 src/mainwindow.cpp}.) Ok this is changing slightly. embroidermodder should boot from the command line regardless of whether it is or is not installed (this helps with testing and running on machines without root). Therefore, it can create an initiation file but it won't rely on its existence to boot: this is what we currently do with settings.ini.
\item Get undo history widget back (BUG).
\item Switch website to a CMake build.
\item Mac Bundle, .tar.gz and .zip source archive.
\item NSIS installer for Windows, Debian package, RPM package
\item GUI frontend for embroider features that aren't supported by embroidermodder: flag selector from a table
\item Update all formats without color to check for edr or rgb files.
\item EmbroideryFLOSS - Color picker that displays catalog numbers and names
\item Setting for reverse scrolling direction (for zoom, vertical pan)
\item Stitching simulation
\item User designed custom fill
\item Keyboard zooming, panning
\item Advanced printing
\item Libembroidery 1.0
\item Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
\item New embroidermodder2.ico 16x16 logo that looks good at that scale.
\item saving dst, pes, jef
\item Settings dialog: notify when the user is switching tabs that the setting has been changed, adding apply button is what would make sense for this to happen.
\item Update language translations
\item Replace KDE4 thumbnailer.
\item Import raster image
\item Statistics from 1.0, needs histogram.
\item SNAP/ORTHO/POLAR
\item Cut/copy allow post-selection
\item Layout into config
\item Notify user of data loss if not saving to an object format.
\item Add which formats to work with to preferences.
\item Cannot open file with \# in the name when opening multiple files but works with opening a single file.
\item Closing settings dialog with the X in the window saves settings rather than discarding them.
\item Otto theme icons: units, render, selectors, what's this icon doesn't  scale
\item Layer manager and Layer switcher dock widget
\item Test that all formats read data in correct scale (format details should match other programs).
\item Custom filter bug -- doesn't save changes in some cases.
\end{enumerate}

\subsection{Fix for Version 2.1}

\subsection{Fix eventually}

\subsection{googletests}

gtests are non-essential, testing is for developers not users so we can
choose our own framework. I think the in-built testing for libembroidery
was good and I want to re-instate it.

\subsection{Qt and dependencies}

I'm switching to SDL2 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

\subsection{Documentation}

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive)
one per project.

\subsection{Social Platform}

So... all the issues and project boards etc. being on Github is all well and good assuming that we have our own copies. But we don't if Github goes down or some other major player takes over the space and we have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between them.

\subsection{JSON data Ideas}

So:

1. Port `settings.ini` to `settings.json`.
2. Place `settings.json` in `\$HOME/.embroidermodder` (or equivalent, see the homedir function in \texttt{gui.c}).
3. Parse JSON using cJSON (we have the new parseJSON function).
4. Better structure for settings data so parse and load JSON is easier and
   there's less junk in global variables. A structure similar to a
5. Python dict that uses constants like the sketch below.

\subsection{Why JSON over ini?}

1. We need to hand-write \emph{a} system because the current system is Qt dependent anyway.
2.  This way we can store more complex data structures in the same system including the layout of the widgets which may be user configured (see Blender and GIMP).
3.  Also it's easier to share information formatted this way between systems because most systems us JSON or XML data: there's better support for converting complex data this way.

\subsection{Sketch of a settings system}

.. literalinclude:: examples/settings\_system.c

This would all be in C, and wouldn't rely on Qt at all. We already use a
system like this in `libembroidery` so hopefully devs on both
would get the pattern.

\subsection{Design}

These are key bits of reasoning behind why the software is built the way
it is.

\subsection{Scripting Overhaul}

Originally Embroidermodder had a terminal widget, this is why we removed
it.

\begin{verbatim}
> ROBIN: I think supporting scripting within Embroidermodder doesn't make
> sense.
>
> All features that use scripting can be part of libembroidery instead.
> Users who are capable of using scripting won't need it, they can alter
> their embroidery files in CSV format, or import pyembroidery to get
> access. It makes maintaining the code a lot more complicated, especially
> if we move away from Qt. Users who don't want the scripting > feature will
> likely be confused by it, since we say that's what  libembroidery,
> embroider and pyembroidery are for.
>
> How about a simpler ``call user shell`` feature? Similar to texmaker we
> just call system on a batch or shell script supplied by the user and it
> processes the file directly then the software reloads the file. Then we
> aren't parsing it directly.
>
> I don't want to change this without Josh's support because it's a fairly
> major change.
>
>> JOSH: I totally agree.
>>
>> I like the idea of scripting just so people that know how to code could
>> write their own designs without needing to fully build the app.
>> Scripting would be a very advanced feature that most users would be
>> confused by. Libembroidery would be a good fit for advanced features.
\end{verbatim}

\subsection{Perennial Jobs}

1. Check for memory leaks
2. Clear compiler warnings on `-Wall\ -ansi\ -pedantic` for C.

\subsection{Developing for Android}

https://developer.android.com/studio/projects/add-native-code

```
apt install google-android-ndk-installer cmake lldb gradle
```

\subsection{Bibilography}

\subsection{Introduction}

\subsection{Basic Features}

\subsection{Move a single stitch in an existing pattern}

1. In the `File` menu, click `Open...`. When the open dialog appears find and select your file by double clicking the name of the file. Alternatively, left click the file once then click the `Open` button.
2. .
3. In the `File` menu

TIP: For users who prefer

\subsection{Convert one pattern to another format}

* In the `File` menu, click `Open...`.
* The
* In the dropdown menu within the save dialog select the

\subsection{Advanced Features}

\subsection{Other Projects}

\subsection{References}

\subsection{Planning}

To see what's planned open the
[Projects](https://github.com/Embroidermodder/Embroidermodder/projects/1)
tab which sorts all of the GitHub Issues into columns.

\subsection{Format Support}

Support for Singer FHE, CHE (Compucon) formats?

\subsection{Embroidermodder Project Coding Standards}

A basic set of guidelines to use when submitting code.

\subsection{Naming Conventions}

Name variables and functions intelligently to minimize the need for
comments. It should be immediately obvious what information it
represents. Short names such as x and y are fine when referring to
coordinates. Short names such as i and j are fine when doing loops.

Variable names should be "camelCase", starting with a lowercase word
followed by uppercase word(s). C++ Class Names should be "CamelCase",
using all uppercase word(s). C Functions that attempt to simulate namespacing,
should be ``nameSpace\_camelCase``.

All files and directories shall be lowercase and contain no spaces.

\subsection{Code Style}

Tabs should not be used when indenting. Setup your IDE or text editor to
use 4 spaces.

\subsection{Braces}

For functions: please put each brace on a new line.

```
void function\_definition(int argument)
{

}
```

For control statements: please put the first brace on the same line.

```
if (condition) {

}
```

Use exceptions sparingly.

Do not use ternary operator (?:) in place of if/else.

Do not repeat a variable name that already occurs in an outer scope.

\subsection{Version Control}

Being an open source project, developers can grab the latest code at any
time and attempt to build it themselves. We try our best to ensure that
it will build smoothly at any time, although occasionally we do break
the build. In these instances, please provide a patch, pull request
which fixes the issue or open an issue and notify us of the problem, as
we may not be aware of it and we can build fine.

Try to group commits based on what they are related to:
features/bugs/comments/graphics/commands/etc...

\subsection{Comments}

When writing code, sometimes there are items that we know can be
improved, incomplete or need special clarification. In these cases, use
the types of comments shown below. They are pretty standard and are
highlighted by many editors to make reviewing code easier. We also use
shell scripts to parse the code to find all of these occurrences so
someone wanting to go on a bug hunt will be able to easily see which
areas of the code need more love.

libembroidery is written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

\begin{lstlisting}
/* C Style Comments */
/* TODO: This code clearly needs more work or further review. */
/* BUG: This code is definitely wrong. It needs fixed. */
/* HACK: This code shouldn't be written this way or I don't feel right about it. There may a better solution */
/* WARNING: Think twice (or more times) before changing this code. I put this here for a good reason. */
/* NOTE: This comment is much more important than lesser comments. */
\end{lstlisting}

\section{Ideas}

\subsection{Why this document}

I've been trying to make this document indirectly through the Github
issues page and the website we're building but I think a
straightforward, plain-text file needs to be the ultimate backup for
this. Then I can have a printout while I'm working on the project.

\subsection{Issues}

\subsubsection{Fix before Version 2}

So I've had a few pieces of web infrastructure fail me recently and I
think it's worth noting. An issue that affects us is an issue that can
effect people who use our software.

\begin{itemize}
\item Googletests require a web connection to update and they update on each
      compilation.
\item Downloading and installing Qt has been a pain for some users (46Gb on
      possibly slow connections). I think it was davieboy64?
\item Github is giving me a server offline (500) error and is still giving a bad
      ping.
\item OpenGL rendering within the application. This will allow for Realistic
      Visualization - Bump Mapping/OpenGL/Gradients?
\item JSON configuration (Started, see \texttt{head\ -n\ 50\ src/mainwindow.cpp.})
      Ok this is changing slightly. embroidermodder should boot from the command
      line regardless of whether it is or is not installed (this helps with
      testing and running on machines without root). Therefore, it can create
      an initiation file but it won't rely on its existence to boot: this is
      what we currently do with settings.ini.
\item Get undo history widget back (BUG).
* Switch website to a CMake build.
* Mac Bundle, .tar.gz and .zip source archive.
* NSIS installer for Windows, Debian package, RPM package
* GUI frontend for embroider features that aren't supported by  embroidermodder: flag selector from a table
* Update all formats without color to check for edr or rgb files.
* EmbroideryFLOSS - Color picker that displays catalog numbers and names
* Setting for reverse scrolling direction (for zoom, vertical pan)
* Stitching simulation
* User designed custom fill
* Keyboard zooming, panning
* Advanced printing
* Libembroidery 1.0
* Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
* New embroidermodder2.ico 16x16 logo that looks good at that scale.
* saving dst, pes, jef
* Settings dialog: notify when the user is switching tabs that the setting has been changed, adding apply button is what would make sense for this to happen.
* Update language translations
* Replace KDE4 thumbnailer.
* Import raster image
* Statistics from 1.0, needs histogram.
* SNAP/ORTHO/POLAR
* Cut/copy allow post-selection
* Layout into config
* Notify user of data loss if not saving to an object format.
* Add which formats to work with to preferences.
* Cannot open file with \# in the name when opening multiple files but  works
  with opening a single file.
* Closing settings dialog with the X in the window saves settings rather than discarding them.
* Otto theme icons: units, render, selectors, what's this icon doesn't scale
* Layer manager and Layer switcher dock widget
*  test that all formats read data in correct scale (format details should match other programs).
* Custom filter bug -- doesn't save changes in some cases.
\end{itemize}

\subsubsection{Fix for Version 2.1}

\subsubsection{Fix eventually}

\subsubsection{googletests}

gtests are non-essential, testing is for developers not users so we can
choose our own framework. I think the in-built testing for libembroidery
was good and I want to re-instate it.

\subsubsection{Qt and dependencies}

I'm switching to SDL2 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

\subsubsection{Documentation}

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive)
one per project.

\subsubsection{Social Platform}

So... all the issues and project boards etc. being on Github is all
well and good assuming that we have our own copies. But we don't if
Github goes down or some other major player takes over the space and we
have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between
them.

\subsection{JSON data Ideas}

So:

1. Port `settings.ini` to `settings.json`.
2. Place `settings.json` in `\$HOME/.embroidermodder` (or equivalent, see the homedir function in `gui.c`).
3. Parse JSON using cJSON (we have the new parseJSON function).
4. Better structure for settings data so parse and load JSON is easier and
   there's less junk in global variables. A structure similar to a Python dict
   that uses constants like the sketch below.

\subsubsection{Why JSON over ini?}

1. We need to hand-write \emph{a} system because the current system is Qt dependent anyway.
2. This way we can store more complex data structures in the same system including the layout of the widgets which may be user configured (see Blender and GIMP).
3. Also it's easier to share information formatted this way between systems because most systems us JSON or XML data: there's better support for converting complex data this way.

\subsubsection{Sketch of a settings system}

%.. literalinclude:: examples/settings\_system.c

This would all be in C, and wouldn't rely on Qt at all. We already use a
system like this in \texttt{libembroidery} so hopefully devs on both
would get the pattern.

\subsection{Design}

These are key bits of reasoning behind why the software is built the way
it is.

Conclusions
===========


Bibliography
============

The Embroidermodder Team \emph{Embroidermodder}
\url{http://www.libembroidery.org} (accessed 3. June. 2022)

achatina *Technical Info*
\url{http://www.achatina.de/sewing/main/TECHNICL.HTM} (accessed 28. Sep. 2021)

KDE Community
**Projects/Liberty/File Formats/Tajima Ternary - KDE Community Wiki**
\url{https://community.kde.org/Projects/Liberty/File_Formats/Tajima_Ternary}
(accessed 28. Sep. 2021)

FineEmb Studio
**FineEmb Studio \guillemotright DST**
\url{https://www.fineemb.com/blog/archives/dst-file-encoding.html}
(accessed 28. Sep. 2021)

EduTech Wiki
**Embroidery format DST - EduTech Wiki**
\url{https://edutechwiki.unige.ch/en/Embroidery_format_DST}
(accessed 28. Sep. 2021)

\chapter{Color Charts}

\section{Built-ins}

\subsection{SVG Colors}

\section{Threads}

\subsection{DXF color table}

\subsection{HUS color table}

\subsection{JEF color table}

\subsection{PCM color table}

\subsection{PEC color table}

\section{Contributing}

\subsection{Version Control}

Being an open source project, developers can grab the latest code at any time
and attempt to build it themselves. We try our best to ensure that it will build smoothly
at any time, although occasionally we do break the build. In these instances,
please provide a patch, pull request which fixes the issue or open an issue and
notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

See the coding style  here (coding-style).

\subsection{Get the Development Build going}

When we switch to releases we recommend using them, unless you're reporting a bug in which case you can check the development build for whether it has been patched. If this applies to you, the current development build is https://github.com/Embroidermodder/Embroidermodder/releases/tag/alpha3[here].

\subsection{To Do}

\begin{itemize}
\item Beta
\begin{itemize}
\item Libembroidery 1.0.
\item Better integrated help: I don't think the help should backend to a html file somewhere on the user's system. A better system would be a custom widget within the program that's searchable.
  * EmbroideryFLOSS - Color picker that displays catalog numbers and names.
  * Custom filter bug -- doesn't save changes in some cases.
  * Advanced printing.
  * Stitching simulation.
\end{itemize}
\item 2.x/ideas
\begin{itemize}
\item User designed custom fill.
\end{itemize}
\end{itemize}

These are key bits of reasoning behind why the GUI is built the way it is.

\section{Translation of the user interface}

In a given table the left column is the default symbol and the right string is the translation.
If the translate function fails to find a translation it returns the default symbol.

So in US English it is an empty table, but in UK English
only the dialectical differences are present.

Ideally, we should support at least the 6 languages spoken at the UN. Quoting
\url{https://www.un.org}

\begin{quote}
\emph{There are six official languages of the UN. These are Arabic, Chinese, English, French, Russian and Spanish.}
\end{quote}

We're adding Hindi, on the grounds that it is one of the most commonly spoken languages and at
least one of the Indian languages should be present.

Written Chinese is generally supported as two different symbol sets and we follow that
convension.

English is supported as two dialects to ensure that the development team is aware of what those
differences are. The code base is written by a mixture of US and UK native English speakers
meaning that only the variable names are consistently one dialect: US English. As for
documentation: it is whatever dialect the writer prefers (but they should maintain consistency
within a text block like this one).

Finally, we have \texttt{default}, which is the dominant language
of the internals of the software. Practically, this is
just US English, but in terms of programming history this
is the \texttt{C locale}.

\subsection{Old action system notes}

Action: the basic system to encode all user input.

This typedef gives structure to the data associated with each action
which, in the code, is referred to by the action id (an int from
the define table above).

\subsection{DESCRIPTION OF STRUCT CONTENTS}

\subsection{label}

The action label is always in US English, lowercase,
seperated with hyphens.

For example: \texttt{new-file}.

\section{Flags}

The bit based flags all collected into a 32-bit integer.

\begin{table}
\begin{tabular}{l l}
bit(s) & description \\
0 & User (0) or system (1) permissions. \\
1-3 & The mode of input. \\
4-8 & The object classes that this action can be applied to. \\
9-10 & What menu (if any) should it be present in. \\ 
11-12 & What
\end{tabular}
\caption{Flags of EM actions}
\end{table}

\subsection{Description}

The string placed in the tooltip describing the action.

\subsection{Original Prompt System}

NOTE: `main()` is run every time the command is started.
Use it to reset variables so they are ready to go.

NOTE: `click()` is run only for left clicks.
Middle clicks are used for panning.
Right clicks bring up the context menu.

NOTE: `move()` is optional. It is run only after
`enableMoveRapidFire()` is called. It
will be called every time the mouse moves until
`disableMoveRapidFire()` is called.

NOTE: `prompt()` is run when Enter is pressed.
`appendPromptHistory` is automatically called before `prompt()`
is called so calling it is only needed for erroneous input.
Any text in the command prompt is sent as an uppercase string.

\chapter{Libembroidery v1.0-alpha}

(Under construction, please wait for v1.0 release.)

Libembroidery is a low-level library for reading, writing, 
and altering digital embroidery files in C. It is part of the Embroidermodder Project
for open source machine embroidery.

Libembroidery is the underlying library that is used by [Embroidermodder 2](http://embroidermodder.org)
and is developed by [The Embroidermodder Team](ref the-embroidermodder-team).
A full list of contributors to the project is maintained in
[the Embroidermodder 2 github](https://github.com/Embroidermodder/embroidermodder)
in the file `CREDITS.md`.
It handles over 45 different embroidery specific formats as well
as several non-embroidery specific vector formats.

It also includes a CLI called `embroider` that allows for better automation of
changes to embroidery files and will be more up-to date than
the Embroidermodder 2 GUI.

\section{Documentation}

Libembroidery is documented as part of the [Embroidermodder 2.0 manual](
\url{https://www.libembroidery.org/emrm-2.0.0-alpha.pdf}).
If you need libembroidery for any non-trivial usage or want to contribute to
the library we advise you read the appropriate design sections of the manual
first. Copies of this manual will be shipped with the packaged version of
libembroidery, but to build it we use the Doxyfile in [the Embroidermodder git
repository](https://github.com/Embroidermodder/embroidermodder).

For more basic usage, `embroider` should have some in-built help starting with:

\begin{lstlisting}
$ embroider --help
\end{lstlisting}

\subsection{License}

Libembroidery is distributed under the permissive zlib licence, see the LICENCE file.

\subsection{Demos}

We're currently trying out some fill techniques which will be demonstrated here
and in the script \texttt{qa\_test.sh}.

\includegraphics[width=0.5\textwidth]{images/logo-spirals.png}

Converts to:

\includegraphics[width=0.5\textwidth]{images/logo_spirals_cross_stitch.png}

\subsection{Build}

libembroidery and EmbroiderModder 2 use CMake builds
so if you are building the project to use as a library we recommend
you run:

.. literalinclude:: ../bin/build\_libembroidery.sh
   :language: bash
   :encoding: latin-1
   :linenos:

This builds both the static and shared versions of the library as well
as the command line program `embroider`.

\chapter{CAD Command Overview}

.. literalinclude:: cad\_review.csv

\section{Actions}

\subsection{ABOUT}
\index{action}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
0 & none & 
\end{tabular}
\end{center}

\subsection{ADD-ARC}
\index{action}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
1 & mouse co-ords & 
\end{tabular}
\end{center}

\subsection{ADD-CIRCLE}
\index{ADD-CIRCLE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
2 & mouse co-ords & 
\end{tabular}
\end{center}

\subsection{ADD-DIM-LEADER}
\index{ADD-DIM-LEADER}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
3 & none & 
\end{tabular}
\end{center}

\subsection{ADD-ELLIPSE}
\index{ADD-ELLIPSE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
4 & none & 
\end{tabular}
\end{center}

\subsection{ADD-GEOMETRY}
\index{ADD-GEOMETRY}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
5 & none & 
\end{tabular}
\end{center}

\subsection{ADD-HORIZONTAL-DIMENSION}
\index{ADD-HORIZONTAL-DIMENSION}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
6 & none & 
\end{tabular}
\end{center}

\subsection{ADD-IMAGE}
\index{ADD-IMAGE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
7 & none & 
\end{tabular}
\end{center}

\subsection{ADD-INFINITE-LINE}
\index{ADD-INFINITE-LINE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
8 & none & 
\end{tabular}
\end{center}

\subsection{ADD-LINE}
\index{ADD-LINE}

\begin{center}
\begin{tabular}{l | l | l}
index & arguments & flags \\
9 & none & 
\end{tabular}
\end{center}

\subsection{ADD-PATH}
\index{ADD-PATH}

index 10

\subsection{ADD-POINT}
\index{ADD-POINT}

index 11

\subsection{ADD-POLYGON}
\index{ADD-POLYGON}

index 12

\subsection{ADD-POLYLINE}
\index{ADD-POLYLINE}

index 13

\subsection{ADD-RAY}
\index{ADD-RAY}

index 14

\subsection{ADD-RECTANGLE}
\index{ADD-RECTANGLE}

index 15

\subsection{ADD-REGULAR-POLYGON}
\index{ADD-REGULAR-POLYGON}

index 16

\subsection{ADD-ROUNDED-RECTANGLE}
\index{action}

index 17

\subsection{ADD-RUBBER}
\index{ADD-RUBBER}

index 18

\subsection{ADD-SLOT}
\index{action}

index 19

\subsection{ADD-TEXT-MULTI}
\index{action}

index 20

\subsection{ADD-TEXT-SINGLE}
\index{action}

index 21

\subsection{ADD-TO-SELECTION}
\index{action}

index 22

\subsection{ADD-TRIANGLE}
\index{action}

index 23

\subsection{ADD-VERTICAL-DIMENSION}
\index{action}

index 24

\subsection{ALERT}
\index{action}

index 25

\subsection{ALLOW-RUBBER}
\index{action}

index 26

\subsection{APPEND-HISTORY}
\index{action}

index 27

\subsection{CALCULATE-ANGLE}
\index{action}

index 28

\subsection{CALCULATE-DISTANCE}
\index{action}

index 29

\subsection{CHANGELOG}
\index{action}

index 30

\subsection{CLEAR-RUBBER}
\index{action}

index 31

\subsection{CLEAR-SELECTION}
\index{action}

index 32

\subsection{COPY}
\index{action}

index 33

\subsection{COPY-SELECTED}
\index{action}

index 34

\subsection{CUT}
\index{action}

index 35

\subsection{CUT-SELECTED}
\index{action}

index 36

\subsection{DAY}
\index{action}

index 37

\subsection{DEBUG}
\index{action}

index 38

\subsection{DELETE-SELECTED}
\index{action}

index 39

\subsection{DESIGN-DETAILS}
\index{action}

index 40

\subsection{DO-NOTHING}
\index{action}

index 41

\subsection{END}
\index{action}

index 42

\subsection{ERROR}
\index{action}

index 43

\subsection{HELP}
\index{action}

index 44

\subsection{ICON}
\index{action}

index 45

\subsection{INIT}
\index{action}

index 46

\subsection{MESSAGEBOX}
\index{action}

index 47, 3 char arrays deliminated by quotes Example Call

\subsection{MIRROR-SELECTED}
\index{action}

index 48

\subsection{MOUSE-X}
\index{action}

index 49

\subsection{MOUSE-Y}
\index{action}

index 50

\subsection{MOVE-SELECTED}
\index{action}

index 51

\subsection{NEW}
\index{action}

index 52

\subsection{NIGHT}
\index{action}

index 53

\subsection{NUM-SELECTED}
\index{action}

index 54

\subsection{OPEN}
\index{action}

index 55

\subsection{PAN}
\index{action}

index 56

\subsection{PASTE}
\index{PASTE}

index 57

\subsection{PASTE-SELECTED}
\index{PASTE-SELECTED}

index 58

\subsection{PERPENDICULAR-DISTANCE}
\index{PERPENDICULAR-DISTANCE}

index 59

\subsection{PLATFORM}
\index{PLATFORM}

index 60

\subsection{PREVIEW-OFF}
\index{PREVIEW-OFF}

index 61

\subsection{PREVIEW-ON}
\index{PREVIEW-ON}

index 62

\subsection{PRINT}
\index{PRINT}

index 63

\subsection{PRINT-AREA}
\index{PRINT-AREA}

index 64

\subsection{QSNAP-X}
\index{QSNAP-X}

index 65

\subsection{QSNAP-Y}
\index{QSNAP-Y}

index 66

\subsection{EXIT}
\index{EXIT}

 index 67

\subsection{REDO}
\index{REDO}

index 68

\subsection{ROTATE-SELECTED}
\index{ROTATE-SELECTED}

index 69

\subsection{RUBBER}
\index{RUBBER}

index 70

\subsection{SCALE-SELECTED}
\index{SCALE-SELECTED}

index 71

\subsection{SELECT-ALL}
\index{SELECT-ALL}

index 72

\subsection{SETTINGS-DIALOG}
\index{action}

index 73

\subsection{SET-BACKGROUND-COLOR}
\index{action}

index 74

\subsection{SET-CROSSHAIR-COLOR}
\index{action}

index 75

\subsection{SET-CURSOR-SHAPE}
\index{action}

index 76

\subsection{SET-GRID-COLOR}
\index{action}

index 77

\subsection{SET-PROMPT-PREFIX}
\index{action}

index 78

\subsection{SET-RUBBER-FILTER}
\index{action}

index 79

\subsection{SET-RUBBER-MODE}
\index{action}

index 80

\subsection{SET-RUBBER-POINT}
\index{action}

index 81

\subsection{SET-RUBBER-TEXT}
\index{action}

index 82

\subsection{SPARE-RUBBER}
\index{action}

index 83

\subsection{TIP-OF-THE-DAY}
\index{action}

index 84

\subsection{TODO}
\index{action}

 index 85

\subsection{UNDO}
\index{action}

 index 86

\subsection{VERSION}
\index{action}

index 87

\subsection{VULCANIZE}
\index{action}

index 88

\subsection{WHATS-THIS}
\index{action}

index 89

\subsection{WINDOW-CLOSE}
\index{action}

index 90

\subsection{WINDOW-CLOSE-ALL}
\index{action}

index 91

\subsection{WINDOW-TILE}
\index{action}

index 92

\subsection{WINDOW-CASCADE}
\index{action}

index 93

\subsection{WINDOW-NEXT}
\index{action}

index 94

\subsection{WINDOW-PREVIOUS}
\index{action}

index 95

\subsection{ZOOM}
\index{action}

 index 96

\subsection{ZOOM-IN}
\index{action}

index 97

\subsection{TEST}
\index{action}

 index 98

\subsection{SLEEP}
\index{action}

index 99

\subsection{LAYER-EDITOR}
\index{action}

index 100

\subsection{MAKE-LAYER-CURRENT}
\index{action}

index 101

\subsection{TEXT-BOLD}
\index{action}

index 102

\subsection{TEXT-ITALIC}
\index{action}

index 103

\subsection{TEXT-UNDERLINE}
\index{action}

index 104

\subsection{TEXT-STRIKEOUT}
\index{action}

index 105

\subsection{TEXT-OVERLINE}
\index{action}

index 106

\subsection{LAYER-PREVIOUS}
\index{action}

index 107

\subsection{ICON16}
\index{action}

index 108

\subsection{ICON24}
\index{action}

index 109

\subsection{ICON32}
\index{action}

index 110

\subsection{ICON48}
\index{action}

index 111

\subsection{ICON64}
\index{action}

index 112

\subsection{ICON128}
\index{action}

index 113

\subsection{SAVE}
\index{action}

index 114

\subsection{SAVEAS}
\index{action}

index 115

\subsection{PAN-REAL-TIME}
\index{action}

index 116

\subsection{PAN-POINT}
\index{action}

index 117

\subsection{PAN-LEFT}
\index{action}

index 118

\subsection{PAN-RIGHT}
\index{action}

index 119

\subsection{PAN-UP}
\index{action}

index 120

\subsection{PAN-DOWN}
\index{action}

index 121

\subsection{ZOOM-REAL-TIME}
\index{action}

index 122

\subsection{ZOOM-PREVIOUS}
\index{action}

index 123

\subsection{ZOOM-WINDOW}
\index{action}

index 124

\subsection{ZOOM-DYNAMIC}
\index{action}

index 125

\subsection{ZOOM-OUT}
\index{action}

index 126

\subsection{ZOOM-EXTENTS}
\index{action}

index 127

\subsection{LAYERS}
\index{action}

index 128

\subsection{LAYER-SELECTOR}
\index{action}

index 129

\subsection{TREBLECLEF}
\index{action}

index 130

\subsection{COLOR-SELECTOR}
\index{action}

index 131

\subsection{LINE-TYPE-SELECTOR}
\index{action}

index 132

\subsection{LINE-WEIGHT-SELECTOR}
\index{action}

index 133

\subsection{ZOOM-SCALE}
\index{action}

index 134

\subsection{ZOOM-CENTER}
\index{action}

index 135

\subsection{HIDE-ALL-LAYERS}
\index{action}

index 136

\subsection{ZOOM-SELECTED}
\index{action}

index 137

\subsection{ZOOM-ALL}
\index{action}

index 138

\subsection{ADD-HEART}
\index{action}

index 139

\subsection{ADD-SINGLE-LINE-TEXT}
\index{action}

index 140

\subsection{SHOW-ALL-LAYERS}
\index{action}

index 141

\subsection{FREEZE-ALL-LAYERS}
\index{action}

index 142

\subsection{THAW-ALL-LAYERS}
\index{action}

index 143

\subsection{LOCK-ALL-LAYERS}
\index{action}

index 144

\subsection{UNLOCK-ALL-LAYERS}
\index{UNLOCK-ALL-LAYERS}

index 145

\subsection{ADD-DOLPHIN}
\index{ADD-DOLPHIN}

index 146

\subsection{ADD-DISTANCE}
\index{ADD-DISTANCE}

index 147

\subsection{LOCATE-POINT}
\index{LOCATE-POINT}

index 148

\subsection{QUICKSELECT}
\index{QUICKSELECT}

index 149

\subsection{SPELLCHECK}
\index{SPELLCHECK}

index 150

\subsection{DISTANCE}
\index{DISTANCE}

index 151

\subsection{MOVE}
\index{MOVE}

index 152

\subsection{QUICKLEADER}
\index{QUICKLEADER}

index 153

\subsection{RGB}
\index{RGB}

 index 154

\subsection{ROTATE}
\index{ROTATE}

index 155

\subsection{SANDBOX}
\index{SANDBOX}

index 156

\subsection{ADD-SNOWFLAKE}
\index{ADD-SNOWFLAKE}

index 157

\subsection{ADD-STAR}
\index{ADD-STAR}

index 158

\subsection{DELETE}
\index{DELETE}

index 159

\subsection{SCALE}
\index{SCALE}

index 160

\subsection{SINGLE-LINE-TEXT}
\index{SINGLE-LINE-TEXT}

index 161

\subsection{SYSWINDOWS}
\index{SYSWINDOWS}

index 162


\subsection{Changelog}

\subsection{Ideas}

Stuff that is now supposed to be generated by Doxygen:

* todo: Bibliography style to plainnat.
* todo: US letter paper version of printed docs.

\chapter{Formats}

\section{Overview}

\subsection{Read/Write Support Levels}

The table of read/write format support levels uses the status levels described here:
%\if{0}

\begin{longtable}{p{4cm} p{8cm}}
\caption{Read/Write Support Levels.}
\label{tab:read-write-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{rw-none} &
Either the format produces no output, reporting an error. Or it produces a
Tajima dst file as an alternative. \\

\texttt{rw-poor} &
A file somewhat similar to our examples is produced. We don't know how well
it runs on machines in practice as we don't have any user reports or personal
tests. \\

\texttt{rw-basic} &
Simple files in this format run well on machines that use this format. \\

\texttt{rw-standard} &
Files with non-standard features work on machines and we have good documentation
on the format. \\

\texttt{rw-reliable} &
All known features don't cause crashes. Almost all work as expected. \\

\texttt{rw-complete} &
All known features of the format work on machines that use this format.
Translations from and to this format preserve all features present in both.
\end{longtable}

These can be split into `r-basic w-none`, for example, if they don't match.

So all formats can, in principle, have good read and good write support, because it's defined in relation to files that we have described the formats for.

\subsection{Test Support Levels}

\begin{longtable}{p{4cm} p{8cm}}
\caption{Test Support Levels.}
\label{tab:test-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{test-none} &
No tests have been written to test the specifics of the format. \\

\texttt{test-basic} &
Stitch Lists and/or colors have read/write tests. \\

\texttt{test-thorough} &
All features of that format has at least one test. \\

\texttt{test-fuzz} &
Can test the format for uses of features that we haven't thought of by feeding
in nonsense that is designed to push possibly dangerous weaknesses to reveal
themselves. \\

\texttt{test-complete} &
Both thorough and fuzz testing is covered.
\end{longtable}

So all formats can, in principle, have complete testing support, because it's
defined in relation to files that we have described the formats for.

\subsection{Documentation Support Levels}

\begin{longtable}{p{4cm} p{8cm}}
\caption{Test Support Levels.}
\label{tab:doc-support} \\
\textbf{Status Label} &
\textbf{Description} \\

\texttt{doc-none} &
We haven't researched this beyond finding example files. \\

\texttt{doc-basic} &
We have a rough sketch of the size and contents of the header if there is one.
We know the basic stitch encoding (if there is one), but not necessarily all
stitch features. \\

\texttt{doc-standard} &
We know some good sources and/or have tested all the features that appear to
exist. They mostly work the way we have described. \\

`doc-good` &
All features that were described somewhere have been covered here or we have
thoroughly tested our ideas against other softwares and hardwares and they work
as expected. \\

`doc-complete` &
There is a known official description and our description covers all the same
features.
\end{longtable}

Not all formats can have complete documentation because it's based on what
information is publically available. So the total score is reported in the table
below based on what level we think is available.

\subsection{Overall Support}

Since the overall support level is the combination of these
4 factors, but rather than summing up their values it's an
issue of the minimum support of the 4.

\begin{table}
\begin{tabular}{l l}
\textbf{Status Label} &
\textbf{Description}
\\
`read-only` &
If write support is none and read support is not none.
\\
`write-only` &
If read support is none and write support is not none.
\\
`unstable` &
If both read and write support are not none but testing or documentation is none.
\\
`basic` &
If all ratings are better than none.
\\
`reliable` &
If all ratings are better than basic.
\\
`complete` &
If all ratings could not reasonably be better (for example any improvements
rely on information that we may never have access to). This is the only status
that can be revoked, since if the format changes or new documentation is
released it is no longer complete.
\\
`experimental` &
For all other scenarios.
\end{tabular}
\caption{.}
\end{table}

\subsection{Table of Format Support Levels}

Overview of documentation support by format.

``.. csv-table::``
``:file: format\_support.csv``

.. literalinclude:: format\_support.csv

* TODO Josh, Review this section and move any info still valid or needing work into TODO comments in the actual libembroidery code. Many items in this list are out of date and do not reflect the current status of libembroidery. When finished, delete this file.
  * Test that all formats read data in correct scale (format details should match other programs)
  * Add which formats to work with to preferences.
  * Check for memory leaks
  * Update all formats without color to check for edr or rgb files
  * Fix issues with DST (VERY important that DST work well)
* todo Support for Singer FHE, CHE (Compucon) formats?

\section{Geometry and Algorithms}

\subsection{To Do}

\subsection{Arduino}

\begin{itemize}
\item Fix emb-outline files
\item Fix thread-color files
\item Logging of Last Stitch Location to External USB Storage(commonly available and easily replaced) ...wait until TRE is available to avoid rework
\item inotool.org - seems like the logical solution for Nightly/CI builds
\item Smoothieboard experiments
\end{itemize}

\subsection{Testing}

* looping test that reads 10 times while running valgrind. See ``embPattern\_loadExternalColorFile()`` Arduino leak note for more info.

\subsection{Development}

If you wish to develop with us you can chat via the contact email
on the website https://libembroidery.org or in the issues tab on the
github page https://github.com/Embroidermodder/Embroidermodder/issues.
People have been polite and friendly in these conversations and I (Robin)
have really enjoyed them.
If we do have any arguments please note we have a
Code of Conduct ``CODE\_OF\_CONDUCT.md`` so there is a consistent policy to
enforce when dealing with these arguments.

The first thing you should try is building from source using the  build advice (build)
above. Then read some of the  manual
\url{https://libembroidery.org/emrm_alpha_a4.pdf} to get the general
layout of the source code and what we are currently planning.

\section{Contributing}

\subsection{Funding}

The easiest way to help is to fund development (see the Donate button above),
since we can't afford to spend a lot of time developing and only have limited
kit to test out libembroidery on.

\subsection{Programming and Engineering}

Should you want to get into the code itself:

* Low level C developers are be needed for the base library \texttt{libembroidery}.
* Low level assembly programmers are needed for translating some of \texttt{libembroidery} to \texttt{EmbroiderBot}.
* Hardware Engineers to help design our own kitbashed embroidery machine \texttt{EmbroiderBot}, one of the original project aims in 2013.
* Scheme developers and C/SDL developers to help build the GUI.
* Scheme developers to help add designs for generating of custom stitch-filled emblems like the heart or dolphi. Note that this happens in Embroidermodder not libembroidery (which assumes that you already have a function available).

\subsection{Writing}

We also need people familiar with the software and the general
machine embroidery ecosystem to contribute to the
documentation (https://github.com/Embroidermodder/www.libembroidery.org).

We need researchers to find references for the documentation: colour tables,
machine specifications etc. The history is murky and often very poorly maintained
so if you know anything from working in the industry that you can share: it'd be
appreciated!

\section{Embroidermodder Project Coding Standards}

A basic set of guidelines to use when submitting code.

Code structure is mre important than style, so first we advise you read
``Design`` and experimenting before getting into the specifics of code style.

\subsection{Where Code Goes}

Anything that deals with the specifics of embroidery file formats, threads,
rendering to images, embroidery machinery or command line interfaces should go 
in \texttt{libembroidery} not here.

\subsection{Where Non-compiled Files Go}

.. todo::
   Like most user interfaces Embroidermodder is mostly data,
   so here we will have a list describing where each CSV goes.

\subsection{Ways in which we break style on purpose}

Most style guides advise you to keep functions short. We make a few pointed
exceptions to this where the overall health and functionality of the source code should benefit.

The `actuator` function will always be a mess and it should be: we're keeping
the total source lines of code down by encoding all user action into a descrete
sequence of strings that are all below \texttt{``\_STRING\_LENGTH``} in length. See
the section on the actuator (TODO) describing why any other solution we could
think  here would mean more more code without a payoff in speed of execution or
clarity.

\section{Version Control}

Being an open source project, developers can grab the latest code at any time and attempt to build it themselves. We try our best to ensure that it will build smoothly at any time, although occasionally we do break the build. In these instances, please provide a patch, pull request which fixes the issue or open an issue and notify us of the problem, as we may not be aware of it and we can build fine.

Try to group commits based on what they are related to: features/bugs/comments/graphics/commands/etc...

\section{Donations}

Creating software that interfaces with hardware is costly. A summary of some of the costs involved:

* Developer time for 2 core developers
* Computer equipment and parts
* Embroidery machinery
* Various electronics for kitbashing Embroiderbot
* Consumable materials (thread, fabric, stabilizer, etc...)

If you have found our software useful, please consider funding further development by donating to the project on Open Collective
(\url{https://opencollective.com/embroidermodder}).

\section{Embroidermodder Project Coding Standards}

Rather than maintain our own standard for style, please defer to
the Python's PEP 7 %\citep{pep7}
for C style and emulating that in C++.

A basic set of guidelines to use when submitting code. Defer to the PEP7 standard with the following additions:

* All files and directories shall be lowercase and contain no spaces.
* Structs and class names should use `LeadingCapitals`.
* Enums and constants should be ``BLOCK\_CAPITALS``.
* Class members and functions without a parent class should be ``snake\_case``.
  With the exception of when one of the words is a ``class`` name from
  libembroidery in which case it has the middle capitals like this:
  ``embArray\_add``.
* Don't use exceptions.
* Don't use ternary operator (?:) in place of if/else.
* Don't repeat a variable name that already occurs in an outer scope.

\section{Version Control}

Being an open source project, developers can grab the latest code at any
time and attempt to build it themselves. We try our best to ensure that
it will build smoothly at any time, although occasionally we do break
the build. In these instances, please provide a patch, pull request
which fixes the issue or open an issue and notify us of the problem, as
we may not be aware of it and we can build fine.

Try to group commits based on what they are related to:
features/bugs/comments/graphics/commands/etc...

\subsection{Comments}

When writing code, sometimes there are items that we know can be
improved, incomplete or need special clarification. In these cases, use
the types of comments shown below. They are pretty standard and are
highlighted by many editors to make reviewing code easier. We also use
shell scripts to parse the code to find all of these occurrences so
someone wanting to go on a bug hunt will be able to easily see which
areas of the code need more love.

libembroidery and Embroidermodder are written in C and adheres to C89 standards. This means
that any C99 or C++ comments will show up as errors when compiling with
gcc. In any C code, you must use:

.. literalinclude:: examples/comment.c

\subsection{Ideas}

\section{Why this document}

I've been trying to make this document indirectly through the Github
issues page and the website we're building but I think a
straightforward, plain-text file needs to be the ultimate backup for
this. Then I can have a printout while I'm working on the project.

\subsection{Qt and dependencies}

I'm switching to SDL2 (which is a whole other conversation) which means
we can ship it with the source code package meaning only a basic build
environment is necessary to build it.

\subsection{Documentation}

Can we treat the website being a duplicate of the docs a non-starter?
I'd be happier with tex/pdf only and (I know this is counter-intuitive)
one per project.

\subsection{Social Platform}

So... all the issues and project boards etc. being on Github is all
well and good assuming that we have our own copies. But we don't if
Github goes down or some other major player takes over the space and we
have to move (again, since this started on SourceForge).

This file is a backup for that which is why I'm repeating myself between
them.

\subsection{Identify the meaning of these TODO items}

.. todo::
   Saving CSV/SVG (rt) + CSV read/write UNKNOWN interpreted as COLOR bug `\#179`

.. todo::
   Lego Mindstorms NXT/EV3 ports and/or commands

\subsection{Progress Chart}

The chart of successful from-to conversions (previously a separate issue)
is something that should appear in the README.

\subsection{Standard}

The criteria for a good Pull Request from an outside developer has these properties, from most to least important:

\if{0}
\begin{itemize}
\item No regressions on testing.
\item Add a feature, bug fix or documentation that is already agreed on through
    GitHub issues or some other way with a core developer.
\item No GUI specific code should be in libembroidery, that's for Embroidermodder.
\item Pedantic/ansi C unless there's a good reason to use another language.
\item Meet the style above (i.e.  PEP 7, Code Lay-out
    \footnote{\url{https://peps.python.org/pep-0007/#code-lay-out}}.
    We'll just fix the style if the code's good and it's not a lot of work.
\item \texttt{embroider} should be in POSIX style as a command line program.
\item No dependancies that aren't ``standard``, i.e. use only the C Standard Library.
\end{itemize}
\fi

\section{Image Fitting}

A currently unsolved problem in development that warrants further research is
the scenario where a user wants to feed embroider an image that can then be .

\subsection{To Place}

A \emph{right-handed coordinate system}\index{right-handed coordinate system}
is one where up is positive and right is
positive. Left-handed is up is positive, left is positive. Screens often use
down is positive, right is positive, including the OpenGL standard so when
switching between graphics formats and stitch formats we need to use a vertical
flip (``embPattern\_flip``).

`0x20` is the space symbol, so when padding either 0 or space is preferred and
in the case of space use the literal ' '.

\subsection{To Do}

We currently need help with:

* Thorough descriptions of each embroidery format.
* Finding resources for each of the branded thread libraries (along with a
  full citation for documentation).
* Finding resources for each geometric algorithm used (along with a full
  citation for documentation).
* Completing the full `--full-test-suite` with no segfaults and at least a
  clear error message (for example ``not implemented yet``).
* Identifying ``best guesses`` for filling in missing information when going
  from, say ``.csv`` to a late ``.pes`` version. What should the default be when
  the data doesn't clarify?
* Improving the written documentation.
* Funding, see the Sponsor button above. We can treat this as ``work`` and
  put far more hours in with broad support in small donations from people who want
  specific features.

Beyond this the development targets are categories sorted into:

* Basic Features
* Code quality and user friendliness
* embroider CLI
* Documentation
* GUI
* electronics development

\subsection{Basic features}

\begin{itemize}
\item Incorporate `\#if 0` ed parts of `libembroidery.c`.
\item Interpret how to write formats that have a read mode from the source
code and vice versa.
\item Document the specifics of the file formats here for embroidery machine
specific formats. Find websites and other sources that break down the binary
formats we currently don't understand.
\item Find more and better documentation of the structure of the headers for the
formats we do understand.
\end{itemize}

\subsection{Code quality and user friendliness}

* Document all structs, macros and functions (will contribute directly
  on the web version).
* Incorporate experimental code, improve support for language bindings.
* Make stitch x, y into an EmbVector.

\subsection{Documentation}

Run `sloccount` on `extern/` and `.` (and ) so we know the
current scale of the project, aim to get this number low. Report the total as
part of the documentation.

Try to get as much of the source code that we maintain into C as possible so
new developers don't need to learn multiple languages to have an effect. This
bars the embedded parts of the code.

\subsection{GUI}

* Make EmbroideryMobile (Android) also backend to `libembroidery` with a Java wrapper.
* Make EmbroideryMobile (iOS) also backend to `libembroidery` with a Swift wrapper.
* Share some of the MobileViewer and iMobileViewer layout with the main EM2. Perhaps combine those 3 into the Embroidermodder repository so there are 4 repositories total.
* Convert layout data to JSON format and use cJSON for parsing.

\section{Development}

\subsection{Contributing}

If you're interested in getting involved, here's some guidance
for new developers. Currently The Embroidermodder Team is all
hobbyists with an interest in making embroidery machines more
open and user friendly. If you'd like to support us in some other way
you can donate to our Open Collective page (click the Donate button) so
we can spend more time working on the project.

All code written for libembroidery should be ANSI C89 compliant
if it is C. Using other languages should only be used where
necessary to support bindings.

\subsection{Debug}

If you wish to help with development, run this debug script and send us the
error log.

\begin{lstlisting}
#!/bin/bash

rm -fr libembroidery-debug

git clone http://github.com/embroidermodder/libembroidery libembroidery-debug
cd libembroidery-debug

cmake -DCMAKE_BUILD_TYPE=DEBUG .
cmake --build . --config=DEBUG

valgrind ./embroider --full-test-suite
\end{lstlisting}

While we will attempt to maintain good results from this script as part of
normal development it should be the first point of failure on any system we
haven't tested or format we understand less.

\subsection{Binary download}

We need a current `embroider` command line program download, so people can update
without building.

Programming principles for the C core
=====================================

End arrays of char arrays with the symbol ``END``, the code will never require
this symbol as an entry.

Define an array as one of 3 kinds: constant, editable or data.

* Constant arrays are defined const and have fixed length matching the data.
* Editable arrays are fixed length, but to a length based on the practical use
  of that array. A dropdown menu can't contain more than 30 items, because we
  don't want to flood the user with options. However it can nest indefinately,
  so it is not restricted to a total number of entries.
* Data arrays is editable and changes total size at runtime to account for user data.

\section{Style rules for arrays}

1.

Libembroidery on Embedded Systems
=================================

The libembroidery library is designed to support embedded environments as well
as desktop, so it can be used in CNC applications.

Originally, the embedded system aspect of the Embroidermodder project was
targeted at the higher end \index{Arduino} prototyping board as part
of a general effort to make our own open source hardware (\index{OSHW}).

However, the task of building the interface for a full OSHW embroidery machine
neatly splits into the tasks of building a user interface to issue the
commands and the rig itself starting with the stepper motors that wire into
this control circuit. A well built control circuit could issue commands to
a variety of different machine layouts (for example many features are not
present on some machines).

\section{Compatible Boards}

We recommend using an \index{Arduino}Arduino Mega 2560 or another board with equal or
greater specs. That being said, we have had success using an Arduino Uno
R3 but this will likely require further optimization and other
improvements to ensure continued compatibility with the Uno. See below
for more information.

\section{Arduino Considerations}

There are two main concerns here: Flash Storage and SRAM.

libembroidery continually outgrows the 32KB of Flash storage on the
Arduino Uno and every time this occurs, a decision has to be made as to
what capabilities should be included or omitted. While reading files is
the main focus on arduino, writing files may also play a bigger role
in the future. Long term, it would be most practical to handle the
inclusion or omission of any feature via a single configuration header
file that the user can modify to suit their needs.

SRAM is in extremely limited supply and it will deplete quickly so any
dynamic allocation should occur early during the setup phase of the
sketch and sparingly or not at all later in the sketch. To help minimize
SRAM consumption on Arduino and ensure libembroidery can be used in any
way the sketch creator desires, it is required that any sketch using
libembroidery must implement event handlers. See the ino-event source
and header files for more information.

There is also an excellent article by Bill Earl on the Adafruit Learning
System
\footnote{\url{http://learn.adafruit.com/memories-of-an-arduino?view=all}}.

\section{Space}

Since a stitch takes 3 bytes of storage and many patterns use more than
10k stitches, we can't assume that the pattern will fit in memory. Therefore
we will need to buffer the current pattern on and off storage in small
chunks. By the same reasoning, we can't load all of one struct beore
looping so we will need functions similar to binaryReadInt16 for each
struct.

This means the EmbArray approach won't work since we need to load
each element and dynamic memory management is unnecessary because
the arrays lie in storage.

.. warning::

   TODO: Replace EmbArray functions with ``embPattern\_`` load functions.

\section{Tables}

All thread tables and large text blocks are too big to compile directly
into the source code. Instead we can package the library with a data packet
that is compiled from an assembly program in raw format so the specific
padding can be controlled.

In the user section above we will make it clear that this file
needs to be loaded on the pattern USB/SD card or the program won't function.

.. warning::

   TODO: Start file with a list of offsets to data with a corresponding table
   to load into with macro constants for each label needed.

\section{Current Pattern Memory Management}

It will be simpler to make one file per EmbArray so we keep an EmbFile*
and a length, so no malloc call is necessary. So there needs to be a consistent
tmpfile naming scheme.

TODO: For each pattern generate a random string of hexadecimal and append it
to the filenames like ``stitchList\_A16F.dat``. Need to check for a file
which indicates that this string has been used already.

\section{Special Notes}

Due to historical reasons and to remain compatible with the Arduino 1.0
IDE, this folder must be called "utility". Refer to the arduino build
process for more info
\footnote{\url{https://arduino.github.io/arduino-cli/0.19/sketch-build-process/}}.

libembroidery relies on the Arduino SD library for reading files. See
the ino-file source and header files for more information.

\section{The Assembly Split}

One problem to the problem of supporting both systems with abundant memory
(such as a 2010s or later desktop) and with scarce memory (such as embedded
systems) is that they don't share the same assembly language. To deal with
this: there will be two equivalent software which are hand engineered to be
similar but one will be in C and the other in the assembly dialects we support.

All assembly will be intended for embedded systems only, since a slightly
smaller set of features will be supported. However, we will write a
`x86` version since that can be tested.

That way the work that has been done to simplify the C code can be applied
to the assembly versions.

\chapter{Electronics development}

\section{Ideas}

Currently experimenting with Fritzing 8 (8), upload netlists to embroiderbot when
they can run simulations using the asm in `libembroidery`.

Create a common assembly for data that is the same across chipsets
``libembrodiery\_data\_internal.s``.

Make the defines part of `embroidery.h` all systems and the function list
`c code only`. That way we can share some development between assembly and C versions.

\chapter{Mobile}

Again, it would help to use the C library we have already developed,
however for Android the supported platform is for Java applications.

\url{https://github.com/java-native-access/jna}

\url{https://github.com/marketplace/actions/setup-android-ndk}

\url{https://developer.android.com/ndk/guides}

See the bindings section for how this is achieved.

Ideas
=====

Janome free designs %\citep{janomeFreeDesigns}
Useful for checking conversion accuracy, since we know they'll conform to the
Janome .jef file type correctly.

Production worksheet example

https://zdigitizing.net/wp-content/uploads/2023/08/Shape-A-4x4-1.pdf

BFC offer their own conversion charts.
https://bfc-creations.com

https://bfc-creations.com/ThreadCharts/BFCThreadConversions/BfcPolytoAdemlodyRayonChart.pdf
They also have large designs split into many parts
https://bfc-creations.com/bfc-machine-embroidery-designs/animal-kingdom/animals/large-animals/bfc1678-large-horse-portrait.html
like this.

madiera official shade card
\url{https://www.madeira.com/fileadmin/user_upload/Downloads/Shade_Cards/MADEIRA_CLASSIC.pdf}

\url{https://www.emblibrary.com/thread-exchange}

\url{https://www.isacordthread.com/}

Brother's official conversion chart
\url{https://www.brother-usa.com/Virdata/SAPHTMLEditorFiles/5329756EC43812B7E1000000CD8620B8.PDF}

Exquisite Thread to other brands conversion chart
\url{https://cdn.shopify.com/s/files/1/0217/7354/files/dime_Thread_Covnversion_Chart_2021.pdf}

\url{https://www.simthreads.com/}
Simthread 63 colors conversion chart
\url{https://cdn.shopify.com/s/files/1/0095/8224/7991/files/Simthread_63_Colors_Conversion_Chart_2020.pdf?v=1613751084}

Coats and Clark https://www.coats.com/en-us/solutions/embroidery-solutions

https://discussions.apple.com/thread/8584571 Accessed 18 Aug 2023

Text Wrapping
https://stackoverflow.com/questions/30350946/can-i-have-text-wrapped-automatically-when-creating-a-pdf-overlay-with-ghostscri

https://physics.emory.edu/faculty/weeks/graphics/howtops2.html

https://forum.qt.io/topic/64963/setting-qicon-with-svg-file-as-a-qaction-icon-problem/3

Sew Simple (owner of Fufu brand?) Pantone matching guide for FuFu Rayon
\url{http://www.zsk.co.nz/web_extra_files/fufus/www.fufus.com.tw/product.html#1}
\url{https://www.sewsimple.com.au/fufu-rayon-embroidery-thread}

\url{https://stackoverflow.com/questions/16286134/imagemagick-how-can-i-work-with-histogram-result}

fineEmbStudio2021
%\fi

\bibliographystyle{unsrtnat}
\bibliography{references}

\appendix

\chapter{Tread Tables}

\section{Arc Threads}

%\include{tables/arc_polyester_colors.tex}

%\include{tables/arc_rayon_colors.tex}

\section{Coats and Clark Rayon Codes}

%\include{tables/coats_and_clark_rayon_colors.tex}

\section{DXF Colors}

Based on the DraftSight color table.

%\include{tables/shv_colors.tex}

\section{Exquisite Polyester Codes}

%\include{tables/exquisite_polyester_colors.tex}

\section{Fufu Threads}

%\include{tables/fufu_polyester_colors.tex}

%\include{tables/fufu_rayon_colors.tex}

\section{Hemingworth Polyester Codes}

%\include{tables/shv_colors.tex}

\section{HUS Colors}

(find a citation)

CSV format: red, green, blue, name, catalog number

.HUS Colors

%\include{tables/hus_colors.tex}

\section{Isacord Polyester Codes}

%\include{tables/isacord_polyester_colors.tex}

\section{Isafil Rayon Codes}

%\include{tables/isafil_rayon_colors.tex}

\section{JEF Colors}

To do: find a citation

%\include{tables/jef_colors.tex}

\section{Madeira Threads}

%\include{tables/madeira_polyester_colors.tex}

%\include{tables/madeira_rayon_colors.tex}

\section{Marathon Polyester Codes}

%\include{tables/shv_colors.tex}

\section{Marathon Rayon Codes}

%\include{tables/shv_colors.tex}

\section{Metro Polyester Code}

%\include{tables/shv_colors.tex}

\section{Pantone Codes}

See \url{https://www.pantone-colours.com/}

%\include{tables/pantone_colors.tex}

\section{PCM Color Codes}

%\include{tables/pcm_colors.tex}

\section{PEC Color Codes}

%\include{tables/pec_colors.tex}

\section{Robinson Anton Polyester Codes}
\index{Robinson Anton}

% \include{tables/robinson_anton_colors.tex}

\section{Sigma Polyester Codes}

%\include{tables/sigma_polyester_colors.tex}

\section{Sulky Rayon Colors}
\index{Sulky}
\index{Rayon}

%\include{tables/sulky_rayon_colors.tex}

\section{SVG Colors}
\index{SVG}

Converted from the table at:
\url{https://www.w3.org/TR/SVGb/types.html#ColorKeywords}

NOTE: This supports both UK and US English names, so the repeated values aren't
an error.

\section{ThreadArt Threads}
\index{ThreadArt}

% \include{tables/threadart_polyester_colors.tex}

% \include{tables/threadart_rayon_colors.tex}

\section{ThreaDelight Polyester Codes}
\index{ThreadDelight}

\section{Z102 Threads}

\include{tables/z102_isacord_polyester_colors.tex}

\section{Licenses}

\include{sections/fdl-1.3.tex}

\printindex

\end{document}
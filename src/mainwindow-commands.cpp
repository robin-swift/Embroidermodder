/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 * Visit https://www.libembroidery.org/refman for advice on altering this file,
 * or read the markdown version in embroidermodder2/docs/refman.
 *
 * MainWindow Commands
 */

#include "embroidermodder.h"

void
MainWindow::stub_implement(QString txt)
{
    qDebug("TODO: %s", qPrintable(txt));
}

void
MainWindow::stub_testing()
{
    QMessageBox::warning(this, tr("Testing Feature"), tr("<b>This feature is in testing.</b>"));
}

void
MainWindow::exit()
{
    qDebug("exit()");
    if (prompt_save_history.setting) {
        prompt->saveHistory("prompt.log", prompt_save_history_as_html.setting);
        /* TODO: get filename from settings */
    }
    qApp->closeAllWindows();
    /* Force the MainWindow destructor to run before exiting.
     * Makes Valgrind "still reachable" happy :)
     */
    this->deleteLater();
}

void
MainWindow::checkForUpdates()
{
    qDebug("checkForUpdates()");
    //TODO: Check website for new versions, commands, etc...
}

QString MainWindow::platformString()
{
    //TODO: Append QSysInfo to string where applicable.
    QString os;
    #if   defined(Q_OS_AIX)
    os = "AIX";
    #elif defined(Q_OS_BSD4)
    os = "BSD 4.4";
    #elif defined(Q_OS_BSDI)
    os = "BSD/OS";
    #elif defined(Q_OS_CYGWIN)
    os = "Cygwin";
    #elif defined(Q_OS_DARWIN)
    os = "Mac OS";
    #elif defined(Q_OS_DGUX)
    os = "DG/UX";
    #elif defined(Q_OS_DYNIX)
    os = "DYNIX/ptx";
    #elif defined(Q_OS_FREEBSD)
    os = "FreeBSD";
    #elif defined(Q_OS_HPUX)
    os = "HP-UX";
    #elif defined(Q_OS_HURD)
    os = "GNU Hurd";
    #elif defined(Q_OS_IRIX)
    os = "SGI Irix";
    #elif defined(Q_OS_LINUX)
    os = "Linux";
    #elif defined(Q_OS_LYNX)
    os = "LynxOS";
    #elif defined(Q_OS_MAC)
    os = "Mac OS";
    #elif defined(Q_OS_MSDOS)
    os = "MS-DOS";
    #elif defined(Q_OS_NETBSD)
    os = "NetBSD";
    #elif defined(Q_OS_OS2)
    os = "OS/2";
    #elif defined(Q_OS_OPENBSD)
    os = "OpenBSD";
    #elif defined(Q_OS_OS2EMX)
    os = "XFree86 on OS/2";
    #elif defined(Q_OS_OSF)
    os = "HP Tru64 UNIX";
    #elif defined(Q_OS_QNX)
    os = "QNX Neutrino";
    #elif defined(Q_OS_RELIANT)
    os = "Reliant UNIX";
    #elif defined(Q_OS_SCO)
    os = "SCO OpenServer 5";
    #elif defined(Q_OS_SOLARIS)
    os = "Sun Solaris";
    #elif defined(Q_OS_SYMBIAN)
    os = "Symbian";
    #elif defined(Q_OS_ULTRIX)
    os = "DEC Ultrix";
    #elif defined(Q_OS_UNIX)
    os = "UNIX BSD/SYSV";
    #elif defined(Q_OS_UNIXWARE)
    os = "UnixWare";
    #elif defined(Q_OS_WIN32)
    os = "Windows";
    #elif defined(Q_OS_WINCE)
    os = "Windows CE";
    #endif
    qDebug("Platform: %s", qPrintable(os));
    return os;
}

void
MainWindow::designDetails()
{
    QGraphicsScene* scene = activeScene();
    if (scene) {
        EmbDetailsDialog dialog(scene, this);
        dialog.exec();
    }
}

void
MainWindow::whatsThisContextHelp()
{
    qDebug("whatsThisContextHelp()");
    QWhatsThis::enterWhatsThisMode();
}

void
MainWindow::print()
{
    qDebug("print()");
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) { mdiWin->print(); }
}

void
MainWindow::tipOfTheDay()
{
    qDebug("tipOfTheDay()");

    QString appDir = qApp->applicationDirPath();

    wizardTipOfTheDay = new QWizard(this);
    wizardTipOfTheDay->setAttribute(Qt::WA_DeleteOnClose);
    wizardTipOfTheDay->setWizardStyle(QWizard::ModernStyle);
    wizardTipOfTheDay->setMinimumSize(550, 400);

    QWizardPage* page = new QWizardPage(wizardTipOfTheDay);

    ImageWidget* imgBanner = new ImageWidget(appDir + "/images/did-you-know.png", wizardTipOfTheDay);

    if (general_current_tip.setting >= listTipOfTheDay.size()) {
        general_current_tip.setting = 0;
    }
    labelTipOfTheDay = new QLabel(listTipOfTheDay.value(general_current_tip.setting), wizardTipOfTheDay);
    labelTipOfTheDay->setWordWrap(true);

    QCheckBox* checkBoxTipOfTheDay = new QCheckBox(tr("&Show tips on startup"), wizardTipOfTheDay);
    checkBoxTipOfTheDay->setChecked(general_tip_of_the_day.setting);
    connect(checkBoxTipOfTheDay, SIGNAL(stateChanged(int)), this, SLOT(checkBoxTipOfTheDayStateChanged(int)));

    QVBoxLayout* layout = new QVBoxLayout(wizardTipOfTheDay);
    layout->addWidget(imgBanner);
    layout->addStrut(1);
    layout->addWidget(labelTipOfTheDay);
    layout->addStretch(1);
    layout->addWidget(checkBoxTipOfTheDay);
    page->setLayout(layout);
    wizardTipOfTheDay->addPage(page);

    wizardTipOfTheDay->setWindowTitle("Tip of the Day");

    //TODO: Add icons to buttons by using wizardTipOfTheDay->setButton(QWizard::CustomButton1, buttonPrevious)
    //TODO: Add icons to buttons by using wizardTipOfTheDay->setButton(QWizard::CustomButton1, buttonNext)
    //TODO: Add icons to buttons by using wizardTipOfTheDay->setButton(QWizard::CustomButton1, buttonClose)
    wizardTipOfTheDay->setButtonText(QWizard::CustomButton1, tr("&Previous"));
    wizardTipOfTheDay->setButtonText(QWizard::CustomButton2, tr("&Next"));
    wizardTipOfTheDay->setButtonText(QWizard::CustomButton3, tr("&Close"));
    wizardTipOfTheDay->setOption(QWizard::HaveCustomButton1, true);
    wizardTipOfTheDay->setOption(QWizard::HaveCustomButton2, true);
    wizardTipOfTheDay->setOption(QWizard::HaveCustomButton3, true);
    connect(wizardTipOfTheDay, SIGNAL(customButtonClicked(int)), this, SLOT(buttonTipOfTheDayClicked(int)));

    QList<QWizard::WizardButton> listTipOfTheDayButtons;
    listTipOfTheDayButtons << QWizard::Stretch << QWizard::CustomButton1
        << QWizard::CustomButton2 << QWizard::CustomButton3;
    wizardTipOfTheDay->setButtonLayout(listTipOfTheDayButtons);

    wizardTipOfTheDay->exec();
}

void
MainWindow::checkBoxTipOfTheDayStateChanged(int checked)
{
    general_tip_of_the_day.setting = checked;
}

void
MainWindow::buttonTipOfTheDayClicked(int button)
{
    qDebug("buttonTipOfTheDayClicked(%d)", button);
    if (button == QWizard::CustomButton1) {
        if (general_current_tip.setting > 0)
            general_current_tip.setting--;
        else
            general_current_tip.setting = listTipOfTheDay.size()-1;
        labelTipOfTheDay->setText(listTipOfTheDay.value(general_current_tip.setting));
    }
    else if (button == QWizard::CustomButton2) {
        general_current_tip.setting++;
        if (general_current_tip.setting >= listTipOfTheDay.size())
            general_current_tip.setting = 0;
        labelTipOfTheDay->setText(listTipOfTheDay.value(general_current_tip.setting));
    }
    else if (button == QWizard::CustomButton3) {
        wizardTipOfTheDay->close();
    }
}

void
MainWindow::help()
{
    qDebug("help()");

    // Open the HTML Help in the default browser
    QUrl helpURL("file:///" + qApp->applicationDirPath() + "/help/doc-index.html");
    QDesktopServices::openUrl(helpURL);

    //TODO: This is how to start an external program. Use this elsewhere...
    //QString program = "firefox";
    //QStringList arguments;
    //arguments << "help/commands.html";
    //QProcess *myProcess = new QProcess(this);
    //myProcess->start(program, arguments);
}

void
MainWindow::changelog()
{
    qDebug("changelog()");

    QUrl changelogURL("help/changelog.html");
    QDesktopServices::openUrl(changelogURL);
}

// Standard Slots
void
MainWindow::undo()
{
    qDebug("undo()");
    QString prefix = prompt->getPrefix();
    if (dockUndoEdit->canUndo()) {
        prompt->setPrefix("Undo " + dockUndoEdit->undoText());
        prompt->appendHistory(QString());
        dockUndoEdit->undo();
        prompt->setPrefix(prefix);
    }
    else {
        prompt->alert("Nothing to undo");
        prompt->setPrefix(prefix);
    }
}

void
MainWindow::redo()
{
    qDebug("redo()");
    QString prefix = prompt->getPrefix();
    if (dockUndoEdit->canRedo()) {
        prompt->setPrefix("Redo " + dockUndoEdit->redoText());
        prompt->appendHistory(QString());
        dockUndoEdit->redo();
        prompt->setPrefix(prefix);
    }
    else {
        prompt->alert("Nothing to redo");
        prompt->setPrefix(prefix);
    }
}

bool MainWindow::isShiftPressed()
{
    return shiftKeyPressedState;
}

void
MainWindow::setShiftPressed()
{
    shiftKeyPressedState = true;
}

void
MainWindow::setShiftReleased()
{
    shiftKeyPressedState = false;
}

// Icons
void
MainWindow::iconResize(int iconSize)
{
    this->setIconSize(QSize(iconSize, iconSize));
    layerSelector->     setIconSize(QSize(iconSize*4, iconSize));
    colorSelector->     setIconSize(QSize(iconSize,   iconSize));
    linetypeSelector->  setIconSize(QSize(iconSize*4, iconSize));
    lineweightSelector->setIconSize(QSize(iconSize*4, iconSize));
    //set the minimum combobox width so the text is always readable
    layerSelector->     setMinimumWidth(iconSize*4);
    colorSelector->     setMinimumWidth(iconSize*2);
    linetypeSelector->  setMinimumWidth(iconSize*4);
    lineweightSelector->setMinimumWidth(iconSize*4);

    // TODO: low-priority: open app with iconSize set to 128. resize the icons to a smaller size.

    general_icon_size.setting = iconSize;
}

MdiWindow*
activeMdiWindow()
{
    qDebug("activeMdiWindow()");
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(_main->mdiArea->activeSubWindow());
    return mdiWin;
}

View*
activeView()
{
    _main->debug_message("activeView()");
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(_main->mdiArea->activeSubWindow());
    if (mdiWin) {
        View* v = mdiWin->gview;
        return v;
    }
    return 0;
}

QGraphicsScene*
activeScene()
{
    _main->debug_message("activeScene()");
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(_main->mdiArea->activeSubWindow());
    if (mdiWin) {
        QGraphicsScene* s = mdiWin->gscene;
        return s;
    }
    return 0;
}

QUndoStack*
activeUndoStack()
{
    _main->debug_message("activeUndoStack()");
    View* v = activeView();
    if (v) {
        QUndoStack* u = v->getUndoStack();
        return u;
    }
    return 0;
}

void
MainWindow::setUndoCleanIcon(bool opened)
{
    dockUndoEdit->updateCleanIcon(opened);
}

void
MainWindow::updateAllViewScrollBars(bool val)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) { mdiWin->showViewScrollBars(val); }
    }
}

void
MainWindow::updateAllViewCrossHairColors(QRgb color)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) { mdiWin->setViewCrossHairColor(color); }
    }
}

void
MainWindow::updateAllViewBackgroundColors(QRgb color)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) { mdiWin->setViewBackgroundColor(color); }
    }
}

void
MainWindow::updateAllViewSelectBoxColors(QRgb colorL, QRgb fillL, QRgb colorR, QRgb fillR, int alpha)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) {
            mdiWin->setViewSelectBoxColors(colorL, fillL, colorR, fillR, alpha);
        }
    }
}

void
MainWindow::updateAllViewGridColors(QRgb color)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) {
            mdiWin->setViewGridColor(color);
        }
    }
}

void
MainWindow::updateAllViewRulerColors(QRgb color)
{
    QList<QMdiSubWindow*> windowList = mdiArea->subWindowList();
    for (int i = 0; i < windowList.count(); ++i) {
        MdiWindow* mdiWin = qobject_cast<MdiWindow*>(windowList.at(i));
        if (mdiWin) {
            mdiWin->setViewRulerColor(color);
        }
    }
}

void
MainWindow::updatePickAddMode(bool val)
{
    selection_mode_pickadd.setting = val;
    dockPropEdit->updatePickAddModeButton(val);
}

void
MainWindow::pickAddModeToggled()
{
    bool val = !selection_mode_pickadd.setting;
    updatePickAddMode(val);
}

// Layer ToolBar
void
MainWindow::makeLayerActive()
{
    qDebug("makeLayerActive()");
    stub_implement("Implement makeLayerActive.");
}

void
MainWindow::layerManager()
{
    qDebug("layerManager()");
    stub_implement("Implement layerManager.");
    LayerManager layman(this, this);
    layman.exec();
}

void
MainWindow::layerPrevious()
{
    qDebug("layerPrevious()");
    stub_implement("Implement layerPrevious.");
}

void
MainWindow::zoomPrevious()
{
    qDebug("zoomPrevious()");
    stub_implement("Implement zoomPrevious.");
}

void
MainWindow::zoomWindow()
{
    qDebug("zoomWindow()");
    View* gview = activeView();
    if (gview) {
        gview->zoomWindow();
    }
}

void
MainWindow::zoomDynamic()
{
    qDebug("zoomDynamic()");
    stub_implement("Implement zoomDynamic.");
}

void
MainWindow::zoomScale()
{
    qDebug("zoomScale()");
    stub_implement("Implement zoomScale.");
}

void
MainWindow::zoomCenter()
{
    qDebug("zoomCenter()");
    stub_implement("Implement zoomCenter.");
}

void
MainWindow::zoomOut()
{
    qDebug("zoomOut()");
    View* gview = activeView();
    if (gview) {
        gview->zoomOut();
    }
}

void
MainWindow::zoomSelected()
{
    qDebug("zoomSelected()");
    View* gview = activeView();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && stack) {
        UndoableNavCommand* cmd = new UndoableNavCommand("ZoomSelected", gview, 0);
        stack->push(cmd);
    }
}

void
MainWindow::zoomAll()
{
    qDebug("zoomAll()");
    stub_implement("Implement zoomAll.");
}

void
MainWindow::zoomExtents()
{
    qDebug("zoomExtents()");
    View* gview = activeView();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && stack) {
        UndoableNavCommand* cmd = new UndoableNavCommand("ZoomExtents", gview, 0);
        stack->push(cmd);
    }
}

void
MainWindow::doNothing()
{
    //This function intentionally does nothing.
    qDebug("doNothing()");
}

void
MainWindow::layerSelectorIndexChanged(int index)
{
    qDebug("layerSelectorIndexChanged(%d)", index);
}

void
MainWindow::colorSelectorIndexChanged(int index)
{
    qDebug("colorSelectorIndexChanged(%d)", index);

    QComboBox* comboBox = qobject_cast<QComboBox*>(sender());
    QRgb newColor;
    if (comboBox) {
        bool ok = 0;
        //TODO: Handle ByLayer and ByBlock and Other...
        newColor = comboBox->itemData(index).toUInt(&ok);
        if (!ok)
            QMessageBox::warning(this, tr("Color Selector Conversion Error"), tr("<b>An error has occured while changing colors.</b>"));
    }
    else {
        QMessageBox::warning(this, tr("Color Selector Pointer Error"), tr("<b>An error has occured while changing colors.</b>"));
    }

    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) { mdiWin->currentColorChanged(newColor); }
}

void
MainWindow::linetypeSelectorIndexChanged(int index)
{
    qDebug("linetypeSelectorIndexChanged(%d)", index);
}

void
MainWindow::lineweightSelectorIndexChanged(int index)
{
    qDebug("lineweightSelectorIndexChanged(%d)", index);
}

void
MainWindow::textFontSelectorCurrentFontChanged(const QFont& font)
{
    qDebug("textFontSelectorCurrentFontChanged()");
    setTextFont(font.family());
}

void
MainWindow::textSizeSelectorIndexChanged(int index)
{
    qDebug("textSizeSelectorIndexChanged(%d)", index);
    // TODO: check that the toReal() conversion is ok
    text_size.setting = qFabs(textSizeSelector->itemData(index).toReal());
}

void
MainWindow::setTextFont(const QString& str)
{
    textFontSelector->setCurrentFont(QFont(str));
    strcpy(text_font.setting, qPrintable(str));
}

void
MainWindow::setTextSize(double num)
{
    text_size.setting = qFabs(num);
    int index = textSizeSelector->findText("Custom", Qt::MatchContains);
    if (index != -1) {
        textSizeSelector->removeItem(index);
    }
    textSizeSelector->addItem("Custom " + QString().setNum(num, 'f', 2) + " pt", num);
    index = textSizeSelector->findText("Custom", Qt::MatchContains);
    if (index != -1) {
        textSizeSelector->setCurrentIndex(index);
    }
}

QString
MainWindow::getCurrentLayer()
{
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        return mdiWin->curLayer;
    }
    return "0";
}

QRgb
MainWindow::getCurrentColor()
{
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        return mdiWin->curColor;
    }
    return 0; //TODO: return color ByLayer
}

QString
MainWindow::getCurrentLineType()
{
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        return mdiWin->curLineType;
    }
    return "ByLayer";
}

QString MainWindow::getCurrentLineWeight()
{
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        return mdiWin->curLineWeight;
    }
    return "ByLayer";
}

void
MainWindow::deletePressed()
{
    qDebug("deletePressed()");
    QApplication::setOverrideCursor(Qt::WaitCursor);
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        mdiWin->deletePressed();
    }
    QApplication::restoreOverrideCursor();
}

void
MainWindow::escapePressed()
{
    qDebug("escapePressed()");
    QApplication::setOverrideCursor(Qt::WaitCursor);
    MdiWindow* mdiWin = qobject_cast<MdiWindow*>(mdiArea->activeSubWindow());
    if (mdiWin) {
        mdiWin->escapePressed();
    }
    QApplication::restoreOverrideCursor();

    end_command();
}

void
MainWindow::toggleGrid()
{
    qDebug("toggleGrid()");
    statusbar->statusBarGridButton->toggle();
}

void
MainWindow::toggleRuler()
{
    qDebug("toggleRuler()");
    statusbar->statusBarRulerButton->toggle();
}

void
MainWindow::toggleLwt()
{
    qDebug("toggleLwt()");
    statusbar->statusBarLwtButton->toggle();
}

void
MainWindow::enablePromptRapidFire()
{
    prompt->enableRapidFire();
}

void
MainWindow::disablePromptRapidFire()
{
    prompt->disableRapidFire();
}

void
MainWindow::enableMoveRapidFire()
{
    View* gview = activeView();
    if (gview) {
        gview->enableMoveRapidFire();
    }
}

void
MainWindow::disableMoveRapidFire()
{
    View* gview = activeView();
    if (gview) {
        gview->disableMoveRapidFire();
    }
}

void
MainWindow::promptHistoryAppended(const QString& txt)
{
    MdiWindow* mdiWin = activeMdiWindow();
    if (mdiWin) {
        mdiWin->promptHistoryAppended(txt);
    }
}

void
MainWindow::logPromptInput(const QString& txt)
{
    MdiWindow* mdiWin = activeMdiWindow();
    if (mdiWin) mdiWin->logPromptInput(txt);
}

void
MainWindow::promptInputPrevious()
{
    MdiWindow* mdiWin = activeMdiWindow();
    if (mdiWin) mdiWin->promptInputPrevious();
}

void
MainWindow::promptInputNext()
{
    MdiWindow* mdiWin = activeMdiWindow();
    if (mdiWin) mdiWin->promptInputNext();
}

ScriptValue
MainWindow::runCommandCore(const QString& cmd, ScriptEnv *context)
{
    int id = get_command_id(qPrintable(cmd));
    if (id >= 0) {
        return command_data[id].main(context);
    }
    qDebug("ERROR: %s not found in command_data.", qPrintable(cmd));
    return script_true;
}

void
MainWindow::runCommand()
{
    QAction* act = qobject_cast<QAction*>(sender());
    if (act) {
        qDebug("runCommand(%s)", qPrintable(act->objectName()));
        prompt->endCommand();
        prompt->setCurrentText(act->objectName());
        prompt->processInput();
    }
}

/* FIXME: reconnect to new command system.
 */
void
MainWindow::runCommandMain(const QString& cmd)
{
    ScriptEnv *context = create_script_env();
    context->context = CONTEXT_MAIN;
    qDebug("runCommandMain(%s)", qPrintable(cmd));
    // TODO: Uncomment this when post-selection is available
    /*
    if (!selection_mode_pick_first.setting) {
        nativeClearSelection();
    }
    */
    runCommandCore(cmd, context);
    free_script_env(context);
}

/* FIXME: reconnect to new command system.
 */
void
MainWindow::runCommandClick(const QString& cmd, double x, double y)
{
    ScriptEnv *context = create_script_env();
    context->context = CONTEXT_CLICK;
    qDebug("runCommandClick(%s, %.2f, %.2f)", qPrintable(cmd), x, y);
    //engine->evaluate(cmd + "_click(" + QString().setNum(x) + "," + QString().setNum(-y) + ")", fileName);
    runCommandCore(cmd, context);
    free_script_env(context);
}

/* FIXME: reconnect to new command system.
 */
void
MainWindow::runCommandMove(const QString& cmd, double x, double y)
{
    ScriptEnv *context = create_script_env();
    context->context = CONTEXT_MOVE;
    qDebug("runCommandMove(%s, %.2f, %.2f)", qPrintable(cmd), x, y);
    //engine->evaluate(cmd + "_move(" + QString().setNum(x) + "," + QString().setNum(-y) + ")", fileName);
    runCommandCore(cmd, context);
    free_script_env(context);
}

/* FIXME: reconnect to new command system.
 */
void
MainWindow::runCommandContext(const QString& cmd, const QString& str)
{
    ScriptEnv *context = create_script_env();
    context->context = CONTEXT_CONTEXT;
    qDebug("runCommandContext(%s, %s)", qPrintable(cmd), qPrintable(str));
    //engine->evaluate(cmd + "_context('" + str.toUpper() + "')", fileName);
    runCommandCore(cmd, context);
    free_script_env(context);
}

/* FIXME: reconnect to new command system.
 * NOTE: Replace any special characters that will cause a syntax error
 */
void
MainWindow::runCommandPrompt(const QString& cmd, const QString& str)
{
    ScriptEnv *context = create_script_env();
    qDebug("runCommandPrompt(%s, %s)", qPrintable(cmd), qPrintable(str));
    context->context = CONTEXT_PROMPT;
    int id = get_command_id(qPrintable(cmd));
    if (id >= 0) {
        QString safeStr = str;
        safeStr.replace("\\", "\\\\");
        safeStr.replace("\'", "\\\'");
        if (prompt->isRapidFireEnabled()) {
            runCommandCore(cmd, context);
        }
        else {
            /* Both branches run the same. */
            runCommandCore(cmd, context);
        }
    }
    free_script_env(context);
}

void
MainWindow::nativeBlinkPrompt()
{
    prompt->startBlinking();
}

void
MainWindow::nativeSetPromptPrefix(const QString& txt)
{
    prompt->setPrefix(txt);
}

void
MainWindow::nativeAppendPromptHistory(const QString& txt)
{
    prompt->appendHistory(txt);
}

void
MainWindow::nativeEnablePromptRapidFire()
{
    enablePromptRapidFire();
}

void
MainWindow::nativeDisablePromptRapidFire()
{
    disablePromptRapidFire();
}

void
MainWindow::nativeEnableMoveRapidFire()
{
    enableMoveRapidFire();
}

void
MainWindow::nativeDisableMoveRapidFire()
{
    disableMoveRapidFire();
}

void
MainWindow::messageBox(const QString& type, const QString& title, const QString& text)
{
    QString msgType = type.toLower();
    if (msgType == "critical") {
        QMessageBox::critical(this, tr(qPrintable(title)), tr(qPrintable(text)));
    }
    else if (msgType == "information") {
        QMessageBox::information(this, tr(qPrintable(title)), tr(qPrintable(text)));
    }
    else if (msgType == "question") {
        QMessageBox::question(this, tr(qPrintable(title)), tr(qPrintable(text)));
    }
    else if (msgType == "warning") {
        QMessageBox::warning(this, tr(qPrintable(title)), tr(qPrintable(text)));
    }
    else {
        QMessageBox::critical   (this, tr("Native MessageBox Error"), tr("Incorrect use of the native messageBox function."));
    }
}

void
MainWindow::nativePrintArea(double x, double y, double w, double h)
{
    qDebug("nativePrintArea(%.2f, %.2f, %.2f, %.2f)", x, y, w, h);
    //TODO: Print Setup Stuff
    print();
}

void
MainWindow::nativeSetBackgroundColor(uint8_t r, uint8_t g, uint8_t b)
{
    display_bg_color.setting = qRgb(r,g,b);
    updateAllViewBackgroundColors(qRgb(r,g,b));
}

void
MainWindow::nativeSetCrossHairColor(uint8_t r, uint8_t g, uint8_t b)
{
    display_crosshair_color.setting = qRgb(r,g,b);
    updateAllViewCrossHairColors(qRgb(r,g,b));
}

void
MainWindow::nativeSetGridColor(uint8_t r, uint8_t g, uint8_t b)
{
    grid_color.setting = qRgb(r,g,b);
    updateAllViewGridColors(qRgb(r,g,b));
}

void
MainWindow::nativeVulcanize()
{
    View* gview = activeView();
    if (gview) {
        gview->vulcanizeRubberRoom();
    }
}

void
MainWindow::nativeClearRubber()
{
    View* gview = activeView();
    if (gview) {
        gview->clearRubberRoom();
    }
}

bool
MainWindow::nativeAllowRubber()
{
    View* gview = activeView();
    if (gview) {
        return gview->allowRubber();
    }
    return false;
}

void
MainWindow::nativeSpareRubber(int64_t id)
{
    View* gview = activeView();
    if (gview) {
        gview->spareRubber(id);
    }
}

void
MainWindow::nativeSetRubberMode(int mode)
{
    View* gview = activeView();
    if (gview) gview->setRubberMode(mode);
}

void
MainWindow::nativeSetRubberPoint(const QString& key, double x, double y)
{
    View* gview = activeView();
    if (gview) gview->setRubberPoint(key, QPointF(x, -y));
}

void
MainWindow::nativeSetRubberText(const QString& key, const QString& txt)
{
    View* gview = activeView();
    if (gview) gview->setRubberText(key, txt);
}

void
MainWindow::nativeAddTextMulti(const QString& str, double x, double y, double rot, bool fill, int rubberMode)
{
}

void
MainWindow::nativeAddTextSingle(const QString& str, double x, double y, double rot, bool fill, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        TextSingleObject* obj = new TextSingleObject(str, x, -y, getCurrentColor());
        obj->setObjectTextFont(text_font.setting);
        obj->setObjectTextSize(text_size.setting);
        obj->setObjectTextStyle(text_style_bold.setting,
                                text_style_italic.setting,
                                text_style_underline.setting,
                                text_style_strikeout.setting,
                                text_style_overline.setting);
        obj->setObjectTextBackward(false);
        obj->setObjectTextUpsideDown(false);
        obj->setRotation(-rot);
        //TODO: single line text fill
        obj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeAddInfiniteLine(double x1, double y1, double x2, double y2, double rot)
{
}

void
MainWindow::nativeAddRay(double x1, double y1, double x2, double y2, double rot)
{
}

void
MainWindow::nativeAddLine(double x1, double y1, double x2, double y2, double rot, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        LineObject* obj = new LineObject(x1, -y1, x2, -y2, getCurrentColor());
        obj->setRotation(-rot);
        obj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeAddTriangle(double x1, double y1, double x2, double y2, double x3, double y3, double rot, bool fill)
{
}

void
MainWindow::nativeAddRectangle(double x, double y, double w, double h, double rot, bool fill, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        RectObject* obj = new RectObject(x, -y, w, -h, getCurrentColor());
        obj->setRotation(-rot);
        obj->setObjectRubberMode(rubberMode);
        //TODO: rect fill
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeAddRoundedRectangle(double x, double y, double w, double h, double rad, double rot, bool fill)
{
}

void
MainWindow::nativeAddArc(EmbArc arc, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* scene = activeScene();
    if (gview && scene) {
        arc.start.y = -arc.start.y;
        arc.mid.y = -arc.mid.y;
        arc.end.y = -arc.end.y;
        ArcObject* arcObj = new ArcObject(arc, getCurrentColor());
        arcObj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(arcObj);
        }
        scene->addItem(arcObj);
        scene->update();
    }
}

void
MainWindow::nativeAddCircle(double centerX, double centerY, double radius, bool fill, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        CircleObject* obj = new CircleObject(centerX, -centerY, radius, getCurrentColor());
        obj->setObjectRubberMode(rubberMode);
        //TODO: circle fill
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeAddSlot(double centerX, double centerY, double diameter, double length, double rot, bool fill, int rubberMode)
{
    //TODO: Use UndoableAddCommand for slots
    /*
    SlotObject* slotObj = new SlotObject(centerX, -centerY, diameter, length, getCurrentColor());
    slotObj->setRotation(-rot);
    slotObj->setObjectRubberMode(rubberMode);
    if (rubberMode) gview->addToRubberRoom(slotObj);
    scene->addItem(slotObj);
    //TODO: slot fill
    scene->update();
    */
}

void
MainWindow::nativeAddEllipse(double centerX, double centerY, double width, double height, double rot, bool fill, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        EllipseObject* obj = new EllipseObject(centerX, -centerY, width, height, getCurrentColor());
        obj->setRotation(-rot);
        obj->setObjectRubberMode(rubberMode);
        //TODO: ellipse fill
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeAddPoint(double x, double y)
{
    View* gview = activeView();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && stack) {
        PointObject* obj = new PointObject(x, -y, getCurrentColor());
        UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
        stack->push(cmd);
    }
}

void
MainWindow::nativeAddRegularPolygon(double centerX, double centerY, quint16 sides, uint8_t mode, double rad, double rot, bool fill)
{
}

//NOTE: This native is different than the rest in that the Y+ is down (scripters need not worry about this)
void
MainWindow::nativeAddPolygon(double startX, double startY, const QPainterPath& p, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        PolygonObject* obj = new PolygonObject(startX, startY, p, getCurrentColor());
        obj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

//NOTE: This native is different than the rest in that the Y+ is down (scripters need not worry about this)
void
MainWindow::nativeAddPolyline(double startX, double startY, const QPainterPath& p, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        PolylineObject* obj = new PolylineObject(startX, startY, p, getCurrentColor());
        obj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

//NOTE: This native is different than the rest in that the Y+ is down (scripters need not worry about this)
void
MainWindow::nativeAddPath(double startX, double startY, const QPainterPath& p, int rubberMode)
{
}

void
MainWindow::nativeAddHorizontalDimension(double x1, double y1, double x2, double y2, double legHeight)
{
}

void
MainWindow::nativeAddVerticalDimension(double x1, double y1, double x2, double y2, double legHeight)
{
}

void
MainWindow::nativeAddImage(const QString& img, double x, double y, double w, double h, double rot)
{
}

void
MainWindow::nativeAddDimLeader(double x1, double y1, double x2, double y2, double rot, int rubberMode)
{
    View* gview = activeView();
    QGraphicsScene* gscene = gview->scene();
    QUndoStack* stack = gview->getUndoStack();
    if (gview && gscene && stack) {
        DimLeaderObject* obj = new DimLeaderObject(x1, -y1, x2, -y2, getCurrentColor());
        obj->setRotation(-rot);
        obj->setObjectRubberMode(rubberMode);
        if (rubberMode) {
            gview->addToRubberRoom(obj);
            gscene->addItem(obj);
            gscene->update();
        }
        else {
            UndoableAddCommand* cmd = new UndoableAddCommand(obj->data(OBJ_NAME).toString(), obj, gview, 0);
            stack->push(cmd);
        }
    }
}

void
MainWindow::nativeSetCursorShape(const QString& str)
{
    View* gview = activeView();
    if (gview) {
        QString shape = str.toLower();
        if (shape == "arrow")
            gview->setCursor(QCursor(Qt::ArrowCursor));
        else if (shape == "uparrow")
            gview->setCursor(QCursor(Qt::UpArrowCursor));
        else if (shape == "cross")
            gview->setCursor(QCursor(Qt::CrossCursor));
        else if (shape == "wait")
            gview->setCursor(QCursor(Qt::WaitCursor));
        else if (shape == "ibeam")           gview->setCursor(QCursor(Qt::IBeamCursor));
        else if (shape == "resizevert")      gview->setCursor(QCursor(Qt::SizeVerCursor));
        else if (shape == "resizehoriz")     gview->setCursor(QCursor(Qt::SizeHorCursor));
        else if (shape == "resizediagleft")  gview->setCursor(QCursor(Qt::SizeBDiagCursor));
        else if (shape == "resizediagright") gview->setCursor(QCursor(Qt::SizeFDiagCursor));
        else if (shape == "move")            gview->setCursor(QCursor(Qt::SizeAllCursor));
        else if (shape == "blank")           gview->setCursor(QCursor(Qt::BlankCursor));
        else if (shape == "splitvert")       gview->setCursor(QCursor(Qt::SplitVCursor));
        else if (shape == "splithoriz")      gview->setCursor(QCursor(Qt::SplitHCursor));
        else if (shape == "handpointing")    gview->setCursor(QCursor(Qt::PointingHandCursor));
        else if (shape == "forbidden")       gview->setCursor(QCursor(Qt::ForbiddenCursor));
        else if (shape == "handopen")        gview->setCursor(QCursor(Qt::OpenHandCursor));
        else if (shape == "handclosed")      gview->setCursor(QCursor(Qt::ClosedHandCursor));
        else if (shape == "whatsthis")       gview->setCursor(QCursor(Qt::WhatsThisCursor));
        else if (shape == "busy")            gview->setCursor(QCursor(Qt::BusyCursor));
        #if QT_VERSION >= 0x040700
        else if (shape == "dragmove")        gview->setCursor(QCursor(Qt::DragMoveCursor));
        else if (shape == "dragcopy")        gview->setCursor(QCursor(Qt::DragCopyCursor));
        else if (shape == "draglink")        gview->setCursor(QCursor(Qt::DragLinkCursor));
        #endif

    }
}

double MainWindow::nativeCalculateAngle(double x1, double y1, double x2, double y2)
{
    return QLineF(x1, -y1, x2, -y2).angle();
}

double MainWindow::nativeCalculateDistance(double x1, double y1, double x2, double y2)
{
    return QLineF(x1, y1, x2, y2).length();
}

double MainWindow::nativePerpendicularDistance(double px, double py, double x1, double y1, double x2, double y2)
{
    QLineF line(x1, y1, x2, y2);
    QLineF norm = line.normalVector();
    double dx = px-x1;
    double dy = py-y1;
    norm.translate(dx, dy);
    QPointF iPoint;
    norm.intersects(line, &iPoint);
    return QLineF(px, py, iPoint.x(), iPoint.y()).length();
}

void
MainWindow::nativeAddToSelection(const QPainterPath path, Qt::ItemSelectionMode mode)
{
}

void
MainWindow::nativeDeleteSelected()
{
    View* gview = activeView();
    if (gview) {
        gview->deleteSelected();
    }
}

void
MainWindow::nativeCutSelected(double x, double y)
{
}

void
MainWindow::nativeCopySelected(double x, double y)
{
}

void
MainWindow::nativePasteSelected(double x, double y)
{
}

void
MainWindow::nativeMoveSelected(double dx, double dy)
{
    View* gview = activeView();
    if (gview) { gview->moveSelected(dx, -dy); }
}

void
MainWindow::nativeScaleSelected(double x, double y, double factor)
{
    if (factor <= 0.0) {
        QMessageBox::critical(this, tr("ScaleFactor Error"),
                                tr("Hi there. If you are not a developer, report this as a bug. "
                                "If you are a developer, your code needs examined, and possibly your head too."));
    }

    View* gview = activeView();
    if (gview) {
        gview->scaleSelected(x, -y, factor);
    }
}

void
MainWindow::nativeRotateSelected(double x, double y, double rot)
{
    View* gview = activeView();
    if (gview) {
        gview->rotateSelected(x, -y, -rot);
    }
}

void
MainWindow::nativeMirrorSelected(double x1, double y1, double x2, double y2)
{
    View* gview = activeView();
    if (gview) {
        gview->mirrorSelected(x1, -y1, x2, -y2);
    }
}

double
MainWindow::nativeQSnapX()
{
    QGraphicsScene* scene = activeScene();
    if (scene) {
        return scene->property("SCENE_QSNAP_POINT").toPointF().x();
    }
    return 0.0;
}

double
MainWindow::nativeQSnapY()
{
    QGraphicsScene* scene = activeScene();
    if (scene) {
        return -scene->property("SCENE_QSNAP_POINT").toPointF().y();
    }
    return 0.0;
}

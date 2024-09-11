/*
 * Embroidermodder 2.
 *
 * Copyright 2011-2024 The Embroidermodder Team
 * Embroidermodder 2 is Open Source Software, see LICENSE.md for licensing terms.
 *
 * Read the reference manual (https://www.libembroidery.org/downloads/emrm.pdf)
 * for advice on altering this file.
 *
 * Qt Wrappers
 */

#include "embroidermodder.h"

/* . */
EmbVector
to_emb_vector(QPointF p)
{
    EmbVector v;
    v.x = p.x();
    v.y = p.y();
    return v;
}

/* . */
QPointF
to_qpointf(EmbVector v)
{
    QPointF p(v.x, v.y);
    return p;
}

/* . */
EmbVector
scale_and_rotate(EmbVector v, double scale, double angle)
{
    EmbVector w;
    double rot = radians(angle);
    double cosRot = cos(rot);
    double sinRot = sin(rot);
    w.x = v.x * scale;
    w.y = v.y * scale;
    w.x = w.x * cosRot - w.y * sinRot;
    w.y = w.x * sinRot + w.y * cosRot;
    return w;    
}

/* . */
EmbVector
find_mouse_snap_point(QList<EmbVector> snap_points, EmbVector mouse_point)
{
    float closest = 1.0e10;
    EmbVector result = snap_points[0];
    int i;
    for (i=0; i<snap_points.count(); i++) {
        float distance = emb_vector_distance(snap_points[i], mouse_point);
        if (distance < closest) {
            closest = distance;
            result = snap_points[i];
        }
    }
    return result;
}

/* . */
EmbArc
emb_arc_set_radius(EmbArc arc, EmbReal radius)
{
    EmbGeometry geometry;
    geometry.object.arc = arc;
    radius = EMB_MAX(radius, 0.0000001);
    EmbVector center = emb_arc_center(geometry);

    EmbVector start = emb_vector_subtract(center, arc.start);
    start = emb_vector_scale(start, radius/emb_vector_length(start));
    arc.start = emb_vector_add(center, start);

    EmbVector mid = emb_vector_subtract(center, arc.mid);
    mid = emb_vector_scale(mid, radius/emb_vector_length(mid));
    arc.mid = emb_vector_add(center, mid);

    EmbVector end = emb_vector_subtract(center, arc.end);
    end = emb_vector_scale(start, radius/emb_vector_length(end));
    arc.end = emb_vector_add(center, end);

    return arc;
}

/* . */
QPixmap
create_pixmap(QString icon)
{
    int id = 0;
    for (int i=0; ; i++) {
        if (!xpm_icon_labels[i]) {
            break;
        }
        if (!strcmp(qPrintable(icon), xpm_icon_labels[i])) {
            id = i;
            break;
        }
    }
    QPixmap pixmap(xpm_icons[id]);
    return pixmap;
}

/* . */
QIcon
create_icon(QString icon)
{
    return QIcon(create_pixmap(icon));
}

/* . */
QIcon
create_swatch(int32_t color)
{
    QPixmap pixmap(16, 16);
    pixmap.fill(QColor(color));
    return QIcon(pixmap); 
}

/* . */
QPushButton *
choose_color_button(QGroupBox* groupbox, int i)
{
    QPushButton* button = new QPushButton(_main->tr("Choose"), groupbox);
    button->setIcon(create_swatch(setting[i].preview.i));
    return button;
}

/* . */
void
set_visibility(QObject *senderObj, const char *key, bool visibility)
{
    QObject* parent = senderObj->parent();
    if (!parent) {
        debug_message("set_visibility called from sender without a parent object");
        return;
    }
    int error = 1;
    if (!strncmp(key, "label", 5)) {
        QLabel* label = parent->findChild<QLabel*>(key);
        if (label) {
            label->setVisible(visibility);
            error = 0;
        }
    }
    if (!strncmp(key, "spinBox", 7)) {
        QDoubleSpinBox* spinbox = parent->findChild<QDoubleSpinBox*>(key);
        if (spinbox) {
            spinbox->setVisible(visibility);
            error = 0;
        }
    }
    if (!strncmp(key, "checkBox", 8)) {
        QCheckBox* checkbox = parent->findChild<QCheckBox*>(key);
        if (checkbox) {
            checkbox->setVisible(visibility);
            error = 0;
        }
    }
    if (!strncmp(key, "comboBox", 8)) {
        QComboBox* combobox = parent->findChild<QComboBox*>(key);
        if (combobox) {
            combobox->setVisible(visibility);
            error = 0;
        }
    }
    if (error) {
        debug_message("Failed to enable/disable the variable");
        debug_message(key);
    }
}

/* . */
void
set_visibility_group(QObject *senderObj, char *keylist[], bool visibility)
{
    int i;
    for (i=0; ; i++) {
        if (!strcmp(keylist[i], "END")) {
            break;
        }
        set_visibility(senderObj, keylist[i], visibility);
    }
}

/* . */
void
set_enabled(QObject *senderObj, const char *key, bool enabled)
{
    QObject* parent = senderObj->parent();
    if (!parent) {
        /* Error reporting. */
        return;
    }
    int error = 1;
    if (!strncmp(key, "label", 5)) {
        QLabel* label = parent->findChild<QLabel*>(key);
        if (label) {
            label->setEnabled(enabled);
            error = 0;
        }
    }
    if (!strncmp(key, "spinBox", 7)) {
        QDoubleSpinBox* spinbox = parent->findChild<QDoubleSpinBox*>(key);
        if (spinbox) {
            spinbox->setEnabled(enabled);
            error = 0;
        }
    }
    if (!strncmp(key, "checkBox", 8)) {
        QCheckBox* checkbox = parent->findChild<QCheckBox*>(key);
        if (checkbox) {
            checkbox->setEnabled(enabled);
            error = 0;
        }
    }
    if (!strncmp(key, "comboBox", 8)) {
        QComboBox* combobox = parent->findChild<QComboBox*>(key);
        if (combobox) {
            combobox->setEnabled(enabled);
            error = 0;
        }
    }
    if (error) {
        debug_message("Failed to enable/disable the variable");
        debug_message(key);
    }
}

/* . */
void
set_enabled_group(QObject *senderObj, char *keylist[], bool enabled)
{
    int i;
    for (i=0; ; i++) {
        if (!strcmp(keylist[i], "END")) {
            break;
        }
        set_enabled(senderObj, keylist[i], enabled);
    }
}

/* . */
void
wait_cursor(void)
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
}

/* . */
void
arrow_cursor(void)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
}

/* . */
void
restore_cursor(void)
{
    QApplication::restoreOverrideCursor();
}

/* . */
QCheckBox*
create_checkbox(QGroupBox* groupbox, QString label, int s, QString icon)
{
    QCheckBox* checkBox = new QCheckBox(translate(qPrintable(label)), groupbox);
    checkBox->setChecked(setting[s].dialog.b);
    QObject::connect(checkBox, &QCheckBox::stateChanged, _main,
        [=](int checked) { setting[s].dialog.b = checked; preview_update(); });
    if (icon != "") {
        checkBox->setIcon(create_icon(icon));
    }
    return checkBox;
}

/* . */
QDoubleSpinBox*
create_spinbox(QGroupBox* groupbox, QString label, int s, double single_step, double lower_bound, double upper_bound)
{
    QDoubleSpinBox* spinbox = new QDoubleSpinBox(groupbox);
    spinbox->setObjectName(label);
    spinbox->setSingleStep(single_step);
    spinbox->setRange(lower_bound, upper_bound);
    spinbox->setValue(setting[s].dialog.r);
    QObject::connect(spinbox, &QDoubleSpinBox::valueChanged, _main,
        [=](double value) { setting[s].dialog.r = value; });
    return spinbox;
}

/* . */
QSpinBox*
create_int_spinbox(QGroupBox* groupbox, QString label, int s, int single_step, int lower_bound, int upper_bound)
{
    QSpinBox* spinbox = new QSpinBox(groupbox);
    spinbox->setObjectName(label);
    spinbox->setSingleStep(single_step);
    spinbox->setRange(lower_bound, upper_bound);
    spinbox->setValue(setting[s].dialog.i);
    QObject::connect(spinbox, &QSpinBox::valueChanged, _main,
        [=](int value) { setting[s].dialog.i = value; });
    return spinbox;
}


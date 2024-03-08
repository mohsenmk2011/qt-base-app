#ifndef HTMLHELPER_H
#define HTMLHELPER_H

#include <QObject>
#include <QRegularExpression>

class HtmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit HtmlHelper(QObject *parent = nullptr);

    static QString removePStyle(const QString &html)
    {
        QRegularExpression regex("<p([^>]*) style=\"([^\"]*)\"([^>]*)>", QRegularExpression::CaseInsensitiveOption);
        QString result = html;
        result.replace(regex, "<p\\1\\3>");
        return result;
    }
    static QString removeP_Br_NewLines(const QString &html)
    {
        // Regular expression to match <p>, <br />, and \n
        QRegularExpression regex("<[pP][^>]*>|</[pP]>|<br\\s*/>|\\n");
        QString result = html;

        // Replace matches with an empty string
        return result.replace(regex, "");
    }

    static QString extractBodyHtml(const QString &html)
    {
        QRegularExpression regex("<body[^>]*>([\\s\\S]*?)<\\/body>", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = regex.match(html);
        if (match.hasMatch()) {
            return match.captured(1);
        } else {
            return "";
        }
    }
    static QString getImgTag(QString source)
    {
        return QString("<img src=\"%1\" />").arg(source);
    }
    // static QString replaceImageSource(QString html, QString oldSrc, QString newSrc)
    // {
    //     QRegExp rx("<img\\b[^>]*\\bsrc=['\"]" + oldSrc + "['\"][^>]*>");
    //     int pos = 0;
    //     while ((pos = rx.indexIn(html, pos)) != -1) {
    //         html.replace(pos, rx.matchedLength(), rx.cap(0).replace(oldSrc, newSrc));
    //         pos += rx.matchedLength();
    //     }
    //     return html;
    // }
signals:

};

#endif // HTMLHELPER_H

#include "pdfpackage.h"

PdfPackage::PdfPackage(QObject* parent)
    : QObject(parent)
{
}

void PdfPackage::setUrl(const QString& data) {
    if (data == m_url) return;
    m_url = data;
    emit urlChanged(m_url);
}

QString PdfPackage::url() const
{ 
    return m_url; 
}

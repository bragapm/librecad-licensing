

/*
UI-only file (.ui.qml): dashboard untuk user biasa.
Logic dihubungkan dari App.qml lewat alias di bawah.
*/
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root
    width: 1100
    height: 680
    color: "#f1f5f9"
    property alias licenseList: licenseList

    // ---- API untuk logic (dipakai dari App.qml) ----
    property alias licenseModel: licenseList.model
    property alias buyButton: buyButton
    property alias logoutButton: logoutButton
    property alias welcomeText: welcomeText.text

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // ---- Header ----
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 72
            color: "#0f172a"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 28
                anchors.rightMargin: 28
                spacing: 16

                Rectangle {
                    width: 40
                    height: 40
                    radius: 10
                    color: "#3b82f6"

                    Text {
                        anchors.centerIn: parent
                        text: "L"
                        color: "white"
                        font.pixelSize: 22
                        font.bold: true
                    }
                }

                Text {
                    text: qsTr("Licensing Portal")
                    color: "white"
                    font.pixelSize: 20
                    font.bold: true
                }

                Item {
                    Layout.fillWidth: true
                }

                Text {
                    id: welcomeText
                    text: qsTr("Halo, User")
                    color: "#cbd5e1"
                    font.pixelSize: 14
                }

                Button {
                    id: logoutButton
                    text: qsTr("Logout")
                    Layout.preferredHeight: 36

                    contentItem: Text {
                        text: logoutButton.text
                        color: "white"
                        font.pixelSize: 13
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 8
                        color: logoutButton.hovered ? "#334155" : "transparent"
                        border.color: "#475569"
                    }
                }
            }
        }

        // ---- Konten ----
        ColumnLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: 28
            spacing: 18

            RowLayout {
                Layout.fillWidth: true

                ColumnLayout {
                    spacing: 2

                    Text {
                        text: qsTr("Lisensi Aktif")
                        color: "#0f172a"
                        font.pixelSize: 26
                        font.bold: true
                    }

                    Text {
                        text: qsTr("Aplikasi yang lisensinya sedang aktif")
                        color: "#64748b"
                        font.pixelSize: 14
                    }
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    id: buyButton
                    text: qsTr("+ Beli Lisensi")
                    Layout.preferredHeight: 44
                    Layout.preferredWidth: 160

                    contentItem: Text {
                        text: buyButton.text
                        color: "white"
                        font.pixelSize: 15
                        font.bold: true
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                    background: Rectangle {
                        radius: 8
                        color: buyButton.down ? "#1d4ed8" : buyButton.hovered ? "#2563eb" : "#3b82f6"
                    }
                }
            }

            // ini yang kita ubah
            /*
              ListModel
              appName
              licenseKey per account
              status
              expiresAt
            */
            ListView {
                id: licenseList
                interactive: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 12

                // Data contoh agar tampil di preview. Diganti data Directus nanti.
                model: ListModel {
                    ListElement {
                        appName: "Braga Designer Pro"
                        licenseKey: "BDP-1234-ABCD-5678"
                        status: "active"
                        expiresAt: "31 Des 2026"
                    }
                    ListElement {
                        appName: "Braga Reporter"
                        licenseKey: "BRP-9876-WXYZ-5432"
                        status: "active"
                        expiresAt: "15 Mar 2027"
                    }
                    ListElement {
                        appName: "Braga Analytics"
                        licenseKey: "BAN-1111-QWER-2222"
                        status: "expiring"
                        expiresAt: "20 Okt 2026"
                    }
                }

                delegate: Rectangle {
                    width: licenseList.width
                    height: 88
                    radius: 12
                    color: "white"
                    border.color: "#e2e8f0"

                    RowLayout {
                        anchors.fill: parent
                        anchors.leftMargin: 20
                        anchors.rightMargin: 20
                        spacing: 16

                        Rectangle {
                            width: 48
                            height: 48
                            radius: 12
                            color: "#dbeafe"

                            Text {
                                anchors.centerIn: parent
                                text: model.appName.charAt(0)
                                color: "#1d4ed8"
                                font.pixelSize: 22
                                font.bold: true
                            }
                        }

                        ColumnLayout {
                            spacing: 4

                            Text {
                                text: model.appName
                                color: "#0f172a"
                                font.pixelSize: 17
                                font.bold: true
                            }

                            Text {
                                text: model.licenseKey
                                color: "#64748b"
                                font.pixelSize: 13
                            }
                        }

                        Item {
                            Layout.fillWidth: true
                        }

                        ColumnLayout {
                            spacing: 6

                            Rectangle {
                                Layout.alignment: Qt.AlignRight
                                width: 96
                                height: 26
                                radius: 13
                                color: model.status === "active" ? "#dcfce7" : "#fef3c7"

                                Text {
                                    anchors.centerIn: parent
                                    text: model.status === "active" ? qsTr("Aktif") : qsTr(
                                                                          "Segera habis")
                                    color: model.status === "active" ? "#15803d" : "#b45309"
                                    font.pixelSize: 12
                                    font.bold: true
                                }
                            }

                            Text {
                                Layout.alignment: Qt.AlignRight
                                text: qsTr("Berlaku s/d ") + model.expiresAt
                                color: "#64748b"
                                font.pixelSize: 12
                            }
                        }
                    }
                }
            }

            Text {
                Layout.alignment: Qt.AlignHCenter
                visible: licenseList.count === 0
                text: qsTr("Belum ada lisensi aktif. Klik \"Beli Lisensi\" untuk memulai.")
                color: "#64748b"
                font.pixelSize: 15
            }
        }
    }
}

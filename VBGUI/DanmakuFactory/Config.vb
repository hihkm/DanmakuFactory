Public Class Config
    Public resx As Integer = 1920
    Public resy As Integer = 1080
    Public displayarea As Double = 1.0
    Public scrollarea As Double = 1.0

    Public scrolltime As Double = 12.0
    Public fixtime As Double = 5.0
    Public density As Integer = 0
    Public fontname As String = "Microsoft YaHei"
    Public fontsize As Integer = 38
    Public opacity As Integer = 200
    Public outline As Integer = 0
    Public shadow As Integer = 1

    Public blockR2L As Boolean = False
    Public blockL2R As Boolean = False
    Public blockTop As Boolean = False
    Public blockBtm As Boolean = False
    Public blockSpecial As Boolean = False
    Public blockColor As Boolean = False
    Public blockRepeat As Boolean = False

    Public statTable As Boolean = False
    Public statHistogram As Boolean = False

    Public Sub WriteConfig()
        WriteConfig("./DanamkuFactoryGUIConfig.txt")
    End Sub

    Public Sub WriteConfig(fileName As String)
        Dim outStr As String = ToString()
        System.IO.File.WriteAllText(fileName, outStr)
    End Sub

    Public Sub ReadConfig()
        ReadConfig("./DanamkuFactoryGUIConfig.txt")
    End Sub

    Public Sub ReadConfig(fileName As String)
        Dim inStr As String
        inStr = System.IO.File.ReadAllText(fileName)
        Dim Settings() As String = inStr.Split(";")
        For Each setStr As String In Settings
            Dim str As String() = setStr.Split(":")
            If str.Length > 1 Then
                Dim key As String = str(0).ToLower()
                Dim value As String = str(1)
                If key = "resx" Then
                    resx = Convert.ToInt32(value)
                ElseIf key = "resy" Then
                    resy = Convert.ToInt32(value)
                ElseIf key = "displayarea" Then
                    displayarea = Convert.ToDouble(value)
                ElseIf key = "scrollarea" Then
                    scrollarea = Convert.ToDouble(value)
                ElseIf key = "scrolltime" Then
                    scrolltime = Convert.ToDouble(value)
                ElseIf key = "density" Then
                    density = Convert.ToInt32(value)
                ElseIf key = "fontsize" Then
                    fontsize = Convert.ToInt32(value)
                ElseIf key = "opacity" Then
                    opacity = Convert.ToInt32(value)
                ElseIf key = "fontname" Then
                    fontname = str(1).Trim()
                ElseIf key = "outline" Then
                    outline = Convert.ToInt32(value)
                ElseIf key = "shadow" Then
                    shadow = Convert.ToInt32(value)
                ElseIf key = "blockr2l" Then
                    blockR2L = Convert.ToBoolean(value)
                ElseIf key = "blockl2r" Then
                    blockL2R = Convert.ToBoolean(value)
                ElseIf key = "blocktop" Then
                    blockTop = Convert.ToBoolean(value)
                ElseIf key = "blockbtm" Then
                    blockBtm = Convert.ToBoolean(value)
                ElseIf key = "blockspecial" Then
                    blockSpecial = Convert.ToBoolean(value)
                ElseIf key = "blockcolor" Then
                    blockColor = Convert.ToBoolean(value)
                ElseIf key = "blockrepeat" Then
                    blockRepeat = Convert.ToBoolean(value)
                ElseIf key = "stattable" Then
                    statTable = Convert.ToBoolean(value)
                ElseIf key = "stathistogram" Then
                    statHistogram = Convert.ToBoolean(value)
                End If
            End If
        Next
    End Sub

    Public Overrides Function ToString() As String
        Dim retStr As String
        retStr = "resX:" + resx.ToString() + ";" +
                 "resY:" + resy.ToString() + ";" +
                 "displayarea:" + displayarea.ToString() + ";" +
                 "scrollarea:" + scrollarea.ToString() + ";" +
                 "scrolltime:" + scrolltime.ToString() + ";" +
                 "fixtime:" + fixtime.ToString() + ";" +
                 "density:" + density.ToString() + ";" +
                 "fontname:" + fontname + ";" +
                 "fontsize:" + fontsize.ToString() + ";" +
                 "opacity:" + opacity.ToString() + ";" +
                 "outline:" + outline.ToString() + ";" +
                 "shadow:" + shadow.ToString() + ";" +
                 "blockR2L:" + blockR2L.ToString() + ";" +
                 "blockL2R:" + blockL2R.ToString() + ";" +
                 "blockTop:" + blockTop.ToString() + ";" +
                 "blockBtm:" + blockBtm.ToString() + ";" +
                 "blockSpecial:" + blockSpecial.ToString() + ";" +
                 "blockColor:" + blockColor.ToString() + ";" +
                 "blockRepeat:" + blockRepeat.ToString() + ";" +
                 "statTable:" + statTable.ToString() + ";" +
                 "statHistogram:" + statHistogram.ToString() + ";"
        Return retStr
    End Function

    '按照 TOP-BOTTOM 的格式输出屏蔽字符串
    Public Function ToBlockString() As String
        Dim blockStr As String = ""

        If blockR2L Then
            blockStr += "r2l"
        End If
        If blockL2R Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "l2r"
        End If
        If blockTop Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "top"
        End If
        If blockBtm Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "bottom"
        End If
        If blockColor Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "color"
        End If
        If blockSpecial Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "special"
        End If
        If blockRepeat Then
            If Not blockStr.Equals("") Then
                blockStr += "-"
            End If
            blockStr += "repeat"
        End If

        Return blockStr
    End Function

    '按照 HISTOGRAM-TABLE 的格式输出统计字符串
    Public Function ToStatString() As String
        Dim statStr As String = ""

        If statHistogram Then
            statStr += "histogram"
        End If
        If statTable Then
            If Not statStr.Equals("") Then
                statStr += "-"
            End If
            statStr += "table"
        End If

        Return statStr
    End Function

    '非法设置修正
    Public Sub Check()
        If resx <= 0 Or resy <= 0 Then
            resx = 1920
            resy = 1080
        End If
        If displayarea <= 0 Or displayarea > 1 Then
            displayarea = 1.0
        End If
        If scrollarea <= 0 Or scrollarea > displayarea Then
            scrollarea = displayarea
        End If
        If scrolltime <= 0 Then
            scrolltime = 12.0
        End If
        If fixtime <= 0 Then
            fixtime = 5.0
        End If
        If density < -1 Then
            density = 0
        End If
        If fontsize <= 0 Then
            fontsize = 38
        End If
        If opacity <= 0 Or opacity > 255 Then
            opacity = 255
        End If
        If outline < 0 Or outline > 4 Then
            outline = 0
        End If
        If shadow < 0 Or shadow > 4 Then
            shadow = 0
        End If
    End Sub
End Class

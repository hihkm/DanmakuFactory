<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class DanmakuSettingDlg
    Inherits System.Windows.Forms.Form

    'Form 重写 Dispose，以清理组件列表。
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Windows 窗体设计器所必需的
    Private components As System.ComponentModel.IContainer

    '注意: 以下过程是 Windows 窗体设计器所必需的
    '可以使用 Windows 窗体设计器修改它。  
    '不要使用代码编辑器修改它。
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.BLK_Rep_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_Special_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_Color_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_Btm_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_Top_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_L2R_CheckBox = New System.Windows.Forms.CheckBox()
        Me.BLK_R2L_CheckBox = New System.Windows.Forms.CheckBox()
        Me.Label9 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.FixTimeNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.ScrollTimeNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label5 = New System.Windows.Forms.Label()
        Me.DensityNUD = New System.Windows.Forms.NumericUpDown()
        Me.DensityRadioButton3 = New System.Windows.Forms.RadioButton()
        Me.DensityRadioButton2 = New System.Windows.Forms.RadioButton()
        Me.DensityRadioButton1 = New System.Windows.Forms.RadioButton()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.Label17 = New System.Windows.Forms.Label()
        Me.OpacityNUD = New System.Windows.Forms.NumericUpDown()
        Me.OutlineNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label4 = New System.Windows.Forms.Label()
        Me.ShadowNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.OpacityLabel = New System.Windows.Forms.Label()
        Me.FontSizeNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.OkButton = New System.Windows.Forms.Button()
        Me.CancelButton = New System.Windows.Forms.Button()
        Me.GroupBox3 = New System.Windows.Forms.GroupBox()
        Me.StatHistogramCheckBox = New System.Windows.Forms.CheckBox()
        Me.StatTableCheckBox = New System.Windows.Forms.CheckBox()
        Me.Label16 = New System.Windows.Forms.Label()
        Me.Label15 = New System.Windows.Forms.Label()
        Me.ResYNUD = New System.Windows.Forms.NumericUpDown()
        Me.ResXNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label14 = New System.Windows.Forms.Label()
        Me.Label13 = New System.Windows.Forms.Label()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.DisplayAreaNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.ScrollAreaNUD = New System.Windows.Forms.NumericUpDown()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.SaveCheckBox = New System.Windows.Forms.CheckBox()
        Me.GroupBox1.SuspendLayout()
        CType(Me.FixTimeNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ScrollTimeNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.DensityNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox2.SuspendLayout()
        CType(Me.OpacityNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.OutlineNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ShadowNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.FontSizeNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.GroupBox3.SuspendLayout()
        CType(Me.ResYNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ResXNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.DisplayAreaNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.ScrollAreaNUD, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.BLK_Rep_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_Special_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_Color_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_Btm_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_Top_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_L2R_CheckBox)
        Me.GroupBox1.Controls.Add(Me.BLK_R2L_CheckBox)
        Me.GroupBox1.Controls.Add(Me.Label9)
        Me.GroupBox1.Controls.Add(Me.Label7)
        Me.GroupBox1.Controls.Add(Me.FixTimeNUD)
        Me.GroupBox1.Controls.Add(Me.Label8)
        Me.GroupBox1.Controls.Add(Me.Label6)
        Me.GroupBox1.Controls.Add(Me.ScrollTimeNUD)
        Me.GroupBox1.Controls.Add(Me.Label5)
        Me.GroupBox1.Controls.Add(Me.DensityNUD)
        Me.GroupBox1.Controls.Add(Me.DensityRadioButton3)
        Me.GroupBox1.Controls.Add(Me.DensityRadioButton2)
        Me.GroupBox1.Controls.Add(Me.DensityRadioButton1)
        Me.GroupBox1.Controls.Add(Me.Label2)
        Me.GroupBox1.Font = New System.Drawing.Font("微软雅黑", 10.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.GroupBox1.Location = New System.Drawing.Point(10, 106)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(395, 193)
        Me.GroupBox1.TabIndex = 1
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "弹幕设置"
        '
        'BLK_Rep_CheckBox
        '
        Me.BLK_Rep_CheckBox.AutoSize = True
        Me.BLK_Rep_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_Rep_CheckBox.Location = New System.Drawing.Point(199, 165)
        Me.BLK_Rep_CheckBox.Name = "BLK_Rep_CheckBox"
        Me.BLK_Rep_CheckBox.Size = New System.Drawing.Size(75, 21)
        Me.BLK_Rep_CheckBox.TabIndex = 19
        Me.BLK_Rep_CheckBox.Text = "内容重复"
        Me.BLK_Rep_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_Special_CheckBox
        '
        Me.BLK_Special_CheckBox.AutoSize = True
        Me.BLK_Special_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_Special_CheckBox.Location = New System.Drawing.Point(11, 165)
        Me.BLK_Special_CheckBox.Name = "BLK_Special_CheckBox"
        Me.BLK_Special_CheckBox.Size = New System.Drawing.Size(51, 21)
        Me.BLK_Special_CheckBox.TabIndex = 18
        Me.BLK_Special_CheckBox.Text = "特殊"
        Me.BLK_Special_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_Color_CheckBox
        '
        Me.BLK_Color_CheckBox.AutoSize = True
        Me.BLK_Color_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_Color_CheckBox.Location = New System.Drawing.Point(102, 165)
        Me.BLK_Color_CheckBox.Name = "BLK_Color_CheckBox"
        Me.BLK_Color_CheckBox.Size = New System.Drawing.Size(63, 21)
        Me.BLK_Color_CheckBox.TabIndex = 17
        Me.BLK_Color_CheckBox.Text = "非白色"
        Me.BLK_Color_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_Btm_CheckBox
        '
        Me.BLK_Btm_CheckBox.AutoSize = True
        Me.BLK_Btm_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_Btm_CheckBox.Location = New System.Drawing.Point(296, 138)
        Me.BLK_Btm_CheckBox.Name = "BLK_Btm_CheckBox"
        Me.BLK_Btm_CheckBox.Size = New System.Drawing.Size(75, 21)
        Me.BLK_Btm_CheckBox.TabIndex = 16
        Me.BLK_Btm_CheckBox.Text = "底部固定"
        Me.BLK_Btm_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_Top_CheckBox
        '
        Me.BLK_Top_CheckBox.AutoSize = True
        Me.BLK_Top_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_Top_CheckBox.Location = New System.Drawing.Point(199, 138)
        Me.BLK_Top_CheckBox.Name = "BLK_Top_CheckBox"
        Me.BLK_Top_CheckBox.Size = New System.Drawing.Size(75, 21)
        Me.BLK_Top_CheckBox.TabIndex = 15
        Me.BLK_Top_CheckBox.Text = "顶部固定"
        Me.BLK_Top_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_L2R_CheckBox
        '
        Me.BLK_L2R_CheckBox.AutoSize = True
        Me.BLK_L2R_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_L2R_CheckBox.Location = New System.Drawing.Point(102, 138)
        Me.BLK_L2R_CheckBox.Name = "BLK_L2R_CheckBox"
        Me.BLK_L2R_CheckBox.Size = New System.Drawing.Size(75, 21)
        Me.BLK_L2R_CheckBox.TabIndex = 14
        Me.BLK_L2R_CheckBox.Text = "左右滚动"
        Me.BLK_L2R_CheckBox.UseVisualStyleBackColor = True
        '
        'BLK_R2L_CheckBox
        '
        Me.BLK_R2L_CheckBox.AutoSize = True
        Me.BLK_R2L_CheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.BLK_R2L_CheckBox.Location = New System.Drawing.Point(11, 138)
        Me.BLK_R2L_CheckBox.Name = "BLK_R2L_CheckBox"
        Me.BLK_R2L_CheckBox.Size = New System.Drawing.Size(75, 21)
        Me.BLK_R2L_CheckBox.TabIndex = 13
        Me.BLK_R2L_CheckBox.Text = "右左滚动"
        Me.BLK_R2L_CheckBox.UseVisualStyleBackColor = True
        '
        'Label9
        '
        Me.Label9.AutoSize = True
        Me.Label9.Location = New System.Drawing.Point(7, 116)
        Me.Label9.Name = "Label9"
        Me.Label9.Size = New System.Drawing.Size(79, 20)
        Me.Label9.TabIndex = 12
        Me.Label9.Text = "按类型屏蔽"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(196, 84)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(23, 20)
        Me.Label7.TabIndex = 11
        Me.Label7.Text = "秒"
        '
        'FixTimeNUD
        '
        Me.FixTimeNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.FixTimeNUD.Location = New System.Drawing.Point(133, 84)
        Me.FixTimeNUD.Maximum = New Decimal(New Integer() {2139062143, 0, 0, 0})
        Me.FixTimeNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.FixTimeNUD.Name = "FixTimeNUD"
        Me.FixTimeNUD.Size = New System.Drawing.Size(57, 23)
        Me.FixTimeNUD.TabIndex = 10
        Me.FixTimeNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(6, 83)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(121, 20)
        Me.Label8.TabIndex = 9
        Me.Label8.Text = "固定弹幕停留时间"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(196, 53)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(23, 20)
        Me.Label6.TabIndex = 8
        Me.Label6.Text = "秒"
        '
        'ScrollTimeNUD
        '
        Me.ScrollTimeNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ScrollTimeNUD.Location = New System.Drawing.Point(133, 53)
        Me.ScrollTimeNUD.Maximum = New Decimal(New Integer() {2139062143, 0, 0, 0})
        Me.ScrollTimeNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.ScrollTimeNUD.Name = "ScrollTimeNUD"
        Me.ScrollTimeNUD.Size = New System.Drawing.Size(57, 23)
        Me.ScrollTimeNUD.TabIndex = 7
        Me.ScrollTimeNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label5
        '
        Me.Label5.AutoSize = True
        Me.Label5.Location = New System.Drawing.Point(6, 52)
        Me.Label5.Name = "Label5"
        Me.Label5.Size = New System.Drawing.Size(121, 20)
        Me.Label5.TabIndex = 6
        Me.Label5.Text = "滚动弹幕通过时间"
        '
        'DensityNUD
        '
        Me.DensityNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.DensityNUD.Location = New System.Drawing.Point(280, 23)
        Me.DensityNUD.Maximum = New Decimal(New Integer() {2139062143, 0, 0, 0})
        Me.DensityNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.DensityNUD.Name = "DensityNUD"
        Me.DensityNUD.Size = New System.Drawing.Size(57, 23)
        Me.DensityNUD.TabIndex = 5
        Me.DensityNUD.Value = New Decimal(New Integer() {50, 0, 0, 0})
        '
        'DensityRadioButton3
        '
        Me.DensityRadioButton3.AutoSize = True
        Me.DensityRadioButton3.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.DensityRadioButton3.Location = New System.Drawing.Point(212, 23)
        Me.DensityRadioButton3.Name = "DensityRadioButton3"
        Me.DensityRadioButton3.Size = New System.Drawing.Size(62, 21)
        Me.DensityRadioButton3.TabIndex = 4
        Me.DensityRadioButton3.TabStop = True
        Me.DensityRadioButton3.Text = "按条数"
        Me.DensityRadioButton3.UseVisualStyleBackColor = True
        '
        'DensityRadioButton2
        '
        Me.DensityRadioButton2.AutoSize = True
        Me.DensityRadioButton2.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.DensityRadioButton2.Location = New System.Drawing.Point(144, 23)
        Me.DensityRadioButton2.Name = "DensityRadioButton2"
        Me.DensityRadioButton2.Size = New System.Drawing.Size(62, 21)
        Me.DensityRadioButton2.TabIndex = 3
        Me.DensityRadioButton2.TabStop = True
        Me.DensityRadioButton2.Text = "不重叠"
        Me.DensityRadioButton2.UseVisualStyleBackColor = True
        '
        'DensityRadioButton1
        '
        Me.DensityRadioButton1.AutoSize = True
        Me.DensityRadioButton1.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.DensityRadioButton1.Location = New System.Drawing.Point(78, 23)
        Me.DensityRadioButton1.Name = "DensityRadioButton1"
        Me.DensityRadioButton1.Size = New System.Drawing.Size(50, 21)
        Me.DensityRadioButton1.TabIndex = 2
        Me.DensityRadioButton1.TabStop = True
        Me.DensityRadioButton1.Text = "无限"
        Me.DensityRadioButton1.UseVisualStyleBackColor = True
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(7, 22)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(65, 20)
        Me.Label2.TabIndex = 1
        Me.Label2.Text = "弹幕密度"
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.Label17)
        Me.GroupBox2.Controls.Add(Me.OpacityNUD)
        Me.GroupBox2.Controls.Add(Me.OutlineNUD)
        Me.GroupBox2.Controls.Add(Me.Label4)
        Me.GroupBox2.Controls.Add(Me.ShadowNUD)
        Me.GroupBox2.Controls.Add(Me.Label3)
        Me.GroupBox2.Controls.Add(Me.OpacityLabel)
        Me.GroupBox2.Controls.Add(Me.FontSizeNUD)
        Me.GroupBox2.Controls.Add(Me.Label1)
        Me.GroupBox2.Font = New System.Drawing.Font("微软雅黑", 10.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.GroupBox2.Location = New System.Drawing.Point(10, 10)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(395, 89)
        Me.GroupBox2.TabIndex = 2
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "文字设置"
        '
        'Label17
        '
        Me.Label17.AutoSize = True
        Me.Label17.Location = New System.Drawing.Point(140, 56)
        Me.Label17.Name = "Label17"
        Me.Label17.Size = New System.Drawing.Size(21, 20)
        Me.Label17.TabIndex = 10
        Me.Label17.Text = "%"
        '
        'OpacityNUD
        '
        Me.OpacityNUD.DecimalPlaces = 1
        Me.OpacityNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.OpacityNUD.Location = New System.Drawing.Point(77, 56)
        Me.OpacityNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.OpacityNUD.Name = "OpacityNUD"
        Me.OpacityNUD.Size = New System.Drawing.Size(57, 23)
        Me.OpacityNUD.TabIndex = 9
        Me.OpacityNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'OutlineNUD
        '
        Me.OutlineNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.OutlineNUD.Location = New System.Drawing.Point(314, 23)
        Me.OutlineNUD.Maximum = New Decimal(New Integer() {4, 0, 0, 0})
        Me.OutlineNUD.Name = "OutlineNUD"
        Me.OutlineNUD.Size = New System.Drawing.Size(57, 23)
        Me.OutlineNUD.TabIndex = 8
        Me.OutlineNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label4
        '
        Me.Label4.AutoSize = True
        Me.Label4.Location = New System.Drawing.Point(271, 23)
        Me.Label4.Name = "Label4"
        Me.Label4.Size = New System.Drawing.Size(37, 20)
        Me.Label4.TabIndex = 7
        Me.Label4.Text = "描边"
        '
        'ShadowNUD
        '
        Me.ShadowNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ShadowNUD.Location = New System.Drawing.Point(195, 24)
        Me.ShadowNUD.Maximum = New Decimal(New Integer() {4, 0, 0, 0})
        Me.ShadowNUD.Name = "ShadowNUD"
        Me.ShadowNUD.Size = New System.Drawing.Size(57, 23)
        Me.ShadowNUD.TabIndex = 6
        Me.ShadowNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(152, 23)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(37, 20)
        Me.Label3.TabIndex = 4
        Me.Label3.Text = "阴影"
        '
        'OpacityLabel
        '
        Me.OpacityLabel.AutoSize = True
        Me.OpacityLabel.Location = New System.Drawing.Point(6, 55)
        Me.OpacityLabel.Name = "OpacityLabel"
        Me.OpacityLabel.Size = New System.Drawing.Size(65, 20)
        Me.OpacityLabel.TabIndex = 2
        Me.OpacityLabel.Text = "不透明度"
        '
        'FontSizeNUD
        '
        Me.FontSizeNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.FontSizeNUD.Location = New System.Drawing.Point(77, 23)
        Me.FontSizeNUD.Maximum = New Decimal(New Integer() {65535, 0, 0, 0})
        Me.FontSizeNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.FontSizeNUD.Name = "FontSizeNUD"
        Me.FontSizeNUD.Size = New System.Drawing.Size(57, 23)
        Me.FontSizeNUD.TabIndex = 1
        Me.FontSizeNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(6, 22)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(65, 20)
        Me.Label1.TabIndex = 0
        Me.Label1.Text = "文字大小"
        '
        'OkButton
        '
        Me.OkButton.Location = New System.Drawing.Point(330, 466)
        Me.OkButton.Name = "OkButton"
        Me.OkButton.Size = New System.Drawing.Size(75, 23)
        Me.OkButton.TabIndex = 3
        Me.OkButton.Text = "确定"
        Me.OkButton.UseVisualStyleBackColor = True
        '
        'CancelButton
        '
        Me.CancelButton.Location = New System.Drawing.Point(240, 466)
        Me.CancelButton.Name = "CancelButton"
        Me.CancelButton.Size = New System.Drawing.Size(75, 23)
        Me.CancelButton.TabIndex = 4
        Me.CancelButton.Text = "取消"
        Me.CancelButton.UseVisualStyleBackColor = True
        '
        'GroupBox3
        '
        Me.GroupBox3.Controls.Add(Me.StatHistogramCheckBox)
        Me.GroupBox3.Controls.Add(Me.StatTableCheckBox)
        Me.GroupBox3.Controls.Add(Me.Label16)
        Me.GroupBox3.Controls.Add(Me.Label15)
        Me.GroupBox3.Controls.Add(Me.ResYNUD)
        Me.GroupBox3.Controls.Add(Me.ResXNUD)
        Me.GroupBox3.Controls.Add(Me.Label14)
        Me.GroupBox3.Controls.Add(Me.Label13)
        Me.GroupBox3.Controls.Add(Me.Label12)
        Me.GroupBox3.Controls.Add(Me.DisplayAreaNUD)
        Me.GroupBox3.Controls.Add(Me.Label11)
        Me.GroupBox3.Controls.Add(Me.ScrollAreaNUD)
        Me.GroupBox3.Controls.Add(Me.Label10)
        Me.GroupBox3.Font = New System.Drawing.Font("微软雅黑", 10.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.GroupBox3.Location = New System.Drawing.Point(10, 306)
        Me.GroupBox3.Name = "GroupBox3"
        Me.GroupBox3.Size = New System.Drawing.Size(395, 154)
        Me.GroupBox3.TabIndex = 2
        Me.GroupBox3.TabStop = False
        Me.GroupBox3.Text = "画面设置"
        '
        'StatHistogramCheckBox
        '
        Me.StatHistogramCheckBox.AutoSize = True
        Me.StatHistogramCheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.StatHistogramCheckBox.Location = New System.Drawing.Point(149, 121)
        Me.StatHistogramCheckBox.Name = "StatHistogramCheckBox"
        Me.StatHistogramCheckBox.Size = New System.Drawing.Size(63, 21)
        Me.StatHistogramCheckBox.TabIndex = 19
        Me.StatHistogramCheckBox.Text = "直方图"
        Me.StatHistogramCheckBox.UseVisualStyleBackColor = True
        '
        'StatTableCheckBox
        '
        Me.StatTableCheckBox.AutoSize = True
        Me.StatTableCheckBox.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.StatTableCheckBox.Location = New System.Drawing.Point(64, 121)
        Me.StatTableCheckBox.Name = "StatTableCheckBox"
        Me.StatTableCheckBox.Size = New System.Drawing.Size(63, 21)
        Me.StatTableCheckBox.TabIndex = 18
        Me.StatTableCheckBox.Text = "统计表"
        Me.StatTableCheckBox.UseVisualStyleBackColor = True
        '
        'Label16
        '
        Me.Label16.AutoSize = True
        Me.Label16.Location = New System.Drawing.Point(7, 119)
        Me.Label16.Name = "Label16"
        Me.Label16.Size = New System.Drawing.Size(37, 20)
        Me.Label16.TabIndex = 17
        Me.Label16.Text = "调试"
        '
        'Label15
        '
        Me.Label15.AutoSize = True
        Me.Label15.Location = New System.Drawing.Point(127, 90)
        Me.Label15.Name = "Label15"
        Me.Label15.Size = New System.Drawing.Size(18, 20)
        Me.Label15.TabIndex = 16
        Me.Label15.Text = "X"
        '
        'ResYNUD
        '
        Me.ResYNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ResYNUD.Location = New System.Drawing.Point(149, 87)
        Me.ResYNUD.Maximum = New Decimal(New Integer() {2139062143, 0, 0, 0})
        Me.ResYNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.ResYNUD.Name = "ResYNUD"
        Me.ResYNUD.Size = New System.Drawing.Size(57, 23)
        Me.ResYNUD.TabIndex = 15
        Me.ResYNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'ResXNUD
        '
        Me.ResXNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ResXNUD.Location = New System.Drawing.Point(64, 87)
        Me.ResXNUD.Maximum = New Decimal(New Integer() {2139062143, 0, 0, 0})
        Me.ResXNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 0})
        Me.ResXNUD.Name = "ResXNUD"
        Me.ResXNUD.Size = New System.Drawing.Size(57, 23)
        Me.ResXNUD.TabIndex = 14
        Me.ResXNUD.Value = New Decimal(New Integer() {1, 0, 0, 0})
        '
        'Label14
        '
        Me.Label14.AutoSize = True
        Me.Label14.Location = New System.Drawing.Point(7, 87)
        Me.Label14.Name = "Label14"
        Me.Label14.Size = New System.Drawing.Size(51, 20)
        Me.Label14.TabIndex = 13
        Me.Label14.Text = "分辨率"
        '
        'Label13
        '
        Me.Label13.AutoSize = True
        Me.Label13.Location = New System.Drawing.Point(209, 52)
        Me.Label13.Name = "Label13"
        Me.Label13.Size = New System.Drawing.Size(21, 20)
        Me.Label13.TabIndex = 12
        Me.Label13.Text = "%"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(209, 22)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(21, 20)
        Me.Label12.TabIndex = 11
        Me.Label12.Text = "%"
        '
        'DisplayAreaNUD
        '
        Me.DisplayAreaNUD.DecimalPlaces = 1
        Me.DisplayAreaNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.DisplayAreaNUD.Location = New System.Drawing.Point(133, 53)
        Me.DisplayAreaNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 65536})
        Me.DisplayAreaNUD.Name = "DisplayAreaNUD"
        Me.DisplayAreaNUD.Size = New System.Drawing.Size(73, 23)
        Me.DisplayAreaNUD.TabIndex = 10
        Me.DisplayAreaNUD.Value = New Decimal(New Integer() {100, 0, 0, 0})
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(7, 53)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(121, 20)
        Me.Label11.TabIndex = 9
        Me.Label11.Text = "全部弹幕显示区域"
        '
        'ScrollAreaNUD
        '
        Me.ScrollAreaNUD.DecimalPlaces = 1
        Me.ScrollAreaNUD.Font = New System.Drawing.Font("微软雅黑", 9.0!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.ScrollAreaNUD.Location = New System.Drawing.Point(133, 22)
        Me.ScrollAreaNUD.Minimum = New Decimal(New Integer() {1, 0, 0, 65536})
        Me.ScrollAreaNUD.Name = "ScrollAreaNUD"
        Me.ScrollAreaNUD.Size = New System.Drawing.Size(73, 23)
        Me.ScrollAreaNUD.TabIndex = 8
        Me.ScrollAreaNUD.Value = New Decimal(New Integer() {100, 0, 0, 0})
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(7, 22)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(121, 20)
        Me.Label10.TabIndex = 2
        Me.Label10.Text = "滚动弹幕显示区域"
        '
        'SaveCheckBox
        '
        Me.SaveCheckBox.AutoSize = True
        Me.SaveCheckBox.Checked = True
        Me.SaveCheckBox.CheckState = System.Windows.Forms.CheckState.Checked
        Me.SaveCheckBox.Font = New System.Drawing.Font("宋体", 10.5!, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, CType(134, Byte))
        Me.SaveCheckBox.Location = New System.Drawing.Point(154, 468)
        Me.SaveCheckBox.Name = "SaveCheckBox"
        Me.SaveCheckBox.Size = New System.Drawing.Size(82, 18)
        Me.SaveCheckBox.TabIndex = 5
        Me.SaveCheckBox.Text = "保存设置"
        Me.SaveCheckBox.UseVisualStyleBackColor = True
        '
        'DanmakuSettingDlg
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(413, 497)
        Me.Controls.Add(Me.SaveCheckBox)
        Me.Controls.Add(Me.GroupBox3)
        Me.Controls.Add(Me.CancelButton)
        Me.Controls.Add(Me.OkButton)
        Me.Controls.Add(Me.GroupBox2)
        Me.Controls.Add(Me.GroupBox1)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog
        Me.Margin = New System.Windows.Forms.Padding(3, 2, 3, 2)
        Me.MaximizeBox = False
        Me.MinimizeBox = False
        Me.Name = "DanmakuSettingDlg"
        Me.ShowInTaskbar = False
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent
        Me.Text = "弹幕设置"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox1.PerformLayout()
        CType(Me.FixTimeNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ScrollTimeNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.DensityNUD, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        CType(Me.OpacityNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.OutlineNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ShadowNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.FontSizeNUD, System.ComponentModel.ISupportInitialize).EndInit()
        Me.GroupBox3.ResumeLayout(False)
        Me.GroupBox3.PerformLayout()
        CType(Me.ResYNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ResXNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.DisplayAreaNUD, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.ScrollAreaNUD, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents GroupBox1 As GroupBox
    Friend WithEvents GroupBox2 As GroupBox
    Friend WithEvents OkButton As Button
    Shadows WithEvents CancelButton As Button
    Friend WithEvents Label3 As Label
    Friend WithEvents FontSizeNUD As NumericUpDown
    Friend WithEvents Label1 As Label
    Friend WithEvents GroupBox3 As GroupBox
    Friend WithEvents OutlineNUD As NumericUpDown
    Friend WithEvents Label4 As Label
    Friend WithEvents ShadowNUD As NumericUpDown
    Friend WithEvents BLK_Rep_CheckBox As CheckBox
    Friend WithEvents BLK_Special_CheckBox As CheckBox
    Friend WithEvents BLK_Color_CheckBox As CheckBox
    Friend WithEvents BLK_Btm_CheckBox As CheckBox
    Friend WithEvents BLK_Top_CheckBox As CheckBox
    Friend WithEvents BLK_L2R_CheckBox As CheckBox
    Friend WithEvents BLK_R2L_CheckBox As CheckBox
    Friend WithEvents Label9 As Label
    Friend WithEvents Label7 As Label
    Friend WithEvents FixTimeNUD As NumericUpDown
    Friend WithEvents Label8 As Label
    Friend WithEvents Label6 As Label
    Friend WithEvents ScrollTimeNUD As NumericUpDown
    Friend WithEvents Label5 As Label
    Friend WithEvents DensityNUD As NumericUpDown
    Friend WithEvents DensityRadioButton3 As RadioButton
    Friend WithEvents DensityRadioButton2 As RadioButton
    Friend WithEvents DensityRadioButton1 As RadioButton
    Friend WithEvents Label2 As Label
    Friend WithEvents OpacityNUD As NumericUpDown
    Friend WithEvents Label15 As Label
    Friend WithEvents ResYNUD As NumericUpDown
    Friend WithEvents ResXNUD As NumericUpDown
    Friend WithEvents Label14 As Label
    Friend WithEvents Label13 As Label
    Friend WithEvents Label12 As Label
    Friend WithEvents DisplayAreaNUD As NumericUpDown
    Friend WithEvents Label11 As Label
    Friend WithEvents ScrollAreaNUD As NumericUpDown
    Friend WithEvents Label10 As Label
    Friend WithEvents StatHistogramCheckBox As CheckBox
    Friend WithEvents StatTableCheckBox As CheckBox
    Friend WithEvents Label16 As Label
    Friend WithEvents Label17 As Label
    Friend WithEvents OpacityLabel As Label
    Friend WithEvents SaveCheckBox As CheckBox
End Class

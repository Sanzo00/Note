# Android学习笔记

## UI界面

### java代码控制UI界面

```java
package com.example.sanzo;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentActivity;
import android.content.DialogInterface;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        FrameLayout framelayout = new FrameLayout(this);
        framelayout.setBackgroundResource(R.mipmap.jb);
        setContentView(framelayout);
        TextView text1 = new TextView(this);
        text1.setText("开始游戏");
        text1.setTextSize(TypedValue.COMPLEX_UNIT_SP, 18);
        text1.setTextColor(Color.rgb(17, 84, 114));
        FrameLayout.LayoutParams params = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT,
            ViewGroup.LayoutParams.WRAP_CONTENT);
        params.gravity = Gravity.CENTER;
        text1.setLayoutParams(params);
        text1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new AlertDialog.Builder(MainActivity.this).setTitle("系统提示")
                        .setMessage("游戏有风险！确定进入吗？")
                        .setPositiveButton("确定",
                                new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {
                                        Log.i("桌面台球", "进入游戏");
                                    }
                                })
                        .setNegativeButton("退出",
                                new DialogInterface.OnClickListener() {
                                    @Override
                                    public void onClick(DialogInterface dialog, int which) {
                                        Log.i("桌面台球", "退出游戏");
                                        finish();
                                    }
                                }).show();
            }
        });
        framelayout.addView(text1);
    }
}
```


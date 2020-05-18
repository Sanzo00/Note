window.$docsify = {
  name: 'Sanzo',
  repo: 'https://github.com/Sanzona',
  coverpage: true, // 首页
  loadNavbar: false, // 导航栏
  loadSidebar: true, // 侧边栏
  subMaxLevel: 5, // 目录级别
  // auto2top: true, //  切换页面自动顶部

  alias: { // 嵌套的侧边栏
    './post/_sidebar.md': './_sidebar.md',
    '.*/_navbar.md': './_navbar.md'
  },

  // 完整配置参数
  search: {
    maxAge: 86400000, // 过期时间，单位毫秒，默认一天
    paths: 'auto', // or 'auto'
    placeholder: '搜索',
    noData: '找不到文件',
    // 搜索标题的最大层级, 1 - 6
    depth: 4,
  },

  // 黑夜模式
  darkMode: {
    dark: {
      background: "#1c2022",
      toggleBtnBg: "#34495e",
      textColor: "#b4b4b4"
    },
    light: {
      background: "white",
      toggleBtnBg: "green",
      textColor: "var(--theme-color)"
    }
  },

  // 字数统计
  count:{
    countable: false,
    fontsize: '0.8em',
    color: 'rgb(90,90,90)',
    language: 'chinese',
    position: "top",
    float: "left",
    isExpected: true, // 时间
  },
  
};

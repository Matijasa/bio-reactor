import { defineConfig } from "astro/config";
import mdx from "@astrojs/mdx";

import remarkMath from "remark-math";
// import rehypeKatex from "rehype-katex";
import rehypeMathjax from "rehype-mathjax";

import sitemap from "@astrojs/sitemap";

import tailwind from "@astrojs/tailwind";

// https://astro.build/config
export default defineConfig({
  site: "https://example.com",
  integrations: [
    mdx({ extendPlugins: "astroDefaults" }),
    sitemap(),
    tailwind(),
  ],
  vite: {
    build: {
      rollupOptions: {
        external: ["**/README.md"],
      },
    },
  },
  markdown: {
    extendDefaultPlugins: true,
    rehypePlugins: [rehypeMathjax],
    remarkPlugins: [remarkMath],
    syntaxHighlight: "shiki",
    drafts: false,
    shikiConfig: {
      theme: "github-light",
    },
  },
});

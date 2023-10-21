package com.example.trei;

import jakarta.servlet.*;
import jakarta.servlet.annotation.WebFilter;
import jakarta.servlet.http.HttpServletResponse;

import java.io.*;

@WebFilter("/*")
public class ResponseFilter implements Filter {

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {
    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        HttpServletResponse httpResponse = (HttpServletResponse) response;
        CharResponseWrapper wrapper = new CharResponseWrapper(httpResponse);

        chain.doFilter(request, wrapper);

        String contentType = wrapper.getContentType();
        System.out.println("contentType: " + contentType);

        if (contentType != null && contentType.contains("text/html")) {

            String originalContent = wrapper.toString();

            int indexOfCloseBodyTag = originalContent.indexOf("</body>") - 1;

            StringBuilder alteredContent = new StringBuilder();
            alteredContent.append(originalContent.substring(0, indexOfCloseBodyTag));

            String copyrightInfo = "<p>Copyright CodeJava.net</p>";
            String closeHTMLTags = "</body></html>";

            alteredContent.append(copyrightInfo);
            alteredContent.append(closeHTMLTags);

            System.out.println("alteredContent: " + alteredContent.toString());

            // Create a new PrintWriter based on the original CharResponseWrapper content
            PrintWriter responseWriter = response.getWriter();
            responseWriter.write(alteredContent.toString());
            responseWriter.flush();
        } else {
            // Content type is not HTML, write the original response to the client
            PrintWriter responseWriter = response.getWriter();
            responseWriter.write(wrapper.toString());
            responseWriter.flush();
        }
    }

    @Override
    public void destroy() {

    }
}

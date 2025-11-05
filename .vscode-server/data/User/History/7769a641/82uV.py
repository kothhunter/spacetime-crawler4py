import re
from urllib.parse import urlparse, urljoin, urldefrag
from bs4 import BeautifulSoup
import json
from collections import Counter

analytics = {
    'unique_urls': set(),
    'word_counts': Counter(),
    'longest_page': {'url': '', 'word_count': 0},
    'subdomains': {},
    'url_patterns': Counter()
}

# Load common English stop words
STOP_WORDS = set([
    'a', 'about', 'above', 'after', 'again', 'against', 'all', 'am', 'an', 
    'and', 'any', 'are', 'aren\'t', 'as', 'at', 'be', 'because', 'been', 
    'before', 'being', 'below', 'between', 'both', 'but', 'by', 'can\'t', 
    'cannot', 'could', 'couldn\'t', 'did', 'didn\'t', 'do', 'does', 
    'doesn\'t', 'doing', 'don\'t', 'down', 'during', 'each', 'few', 'for', 
    'from', 'further', 'had', 'hadn\'t', 'has', 'hasn\'t', 'have', 
    'haven\'t', 'having', 'he', 'he\'d', 'he\'ll', 'he\'s', 'her', 'here', 
    'here\'s', 'hers', 'herself', 'him', 'himself', 'his', 'how', 'how\'s', 
    'i', 'i\'d', 'i\'ll', 'i\'m', 'i\'ve', 'if', 'in', 'into', 'is', 
    'isn\'t', 'it', 'it\'s', 'its', 'itself', 'let\'s', 'me', 'more', 
    'most', 'mustn\'t', 'my', 'myself', 'no', 'nor', 'not', 'of', 'off', 
    'on', 'once', 'only', 'or', 'other', 'ought', 'our', 'ours', 
    'ourselves', 'out', 'over', 'own', 'same', 'shan\'t', 'she', 'she\'d', 
    'she\'ll', 'she\'s', 'should', 'shouldn\'t', 'so', 'some', 'such', 
    'than', 'that', 'that\'s', 'the', 'their', 'theirs', 'them', 
    'themselves', 'then', 'there', 'there\'s', 'these', 'they', 'they\'d', 
    'they\'ll', 'they\'re', 'they\'ve', 'this', 'those', 'through', 'to', 
    'too', 'under', 'until', 'up', 'very', 'was', 'wasn\'t', 'we', 'we\'d', 
    'we\'ll', 'we\'re', 'we\'ve', 'were', 'weren\'t', 'what', 'what\'s', 
    'when', 'when\'s', 'where', 'where\'s', 'which', 'while', 'who', 
    'who\'s', 'whom', 'why', 'why\'s', 'with', 'won\'t', 'would', 
    'wouldn\'t', 'you', 'you\'d', 'you\'ll', 'you\'re', 'you\'ve', 'your', 
    'yours', 'yourself', 'yourselves'
])

def get_url_pattern(url):
    """Extract URL pattern by replacing dates and numbers with placeholders"""
    parsed = urlparse(url)
    path = parsed.path
    
    # Replace date patterns: YYYY-MM-DD, YYYY-MM, YYYY/MM/DD, etc.
    path = re.sub(r'\d{4}-\d{2}-\d{2}', 'DATE', path)
    path = re.sub(r'\d{4}-\d{2}', 'DATE', path)
    path = re.sub(r'\d{4}/\d{2}/\d{2}', 'DATE', path)
    path = re.sub(r'\d{4}/\d{2}', 'DATE', path)
    
    # Replace other numbers
    path = re.sub(r'\d+', 'N', path)
    
    # Combine with domain and query pattern
    query_pattern = 'Q' if parsed.query else ''
    pattern = f"{parsed.netloc}{path}{query_pattern}"
    
    return pattern

def is_url_trap(url):
    """Detect if this URL is part of a repetitive trap"""
    pattern = get_url_pattern(url)
    analytics['url_patterns'][pattern] += 1
    
    # If we've seen this pattern more than 20 times, it's a trap
    if analytics['url_patterns'][pattern] > 20:
        print(f"⚠️ TRAP DETECTED: Pattern '{pattern}' seen {analytics['url_patterns'][pattern]} times. Skipping: {url}")
        return True
    
    return False
  
def scraper(url, resp):
    links = extract_next_links(url, resp)
    return [link for link in links if is_valid(link)]

def extract_next_links(url, resp):
    # Implementation required.
    # url: the URL that was used to get the page
    # resp.url: the actual url of the page
    # resp.status: the status code returned by the server. 200 is OK, you got the page. Other numbers mean that there was some kind of problem.
    # resp.error: when status is not 200, you can check the error here, if needed.
    # resp.raw_response: this is where the page actually is. More specifically, the raw_response has two parts:
    #         resp.raw_response.url: the url, again
    #         resp.raw_response.content: the content of the page!
    # Return a list with the hyperlinks (as strings) scrapped from resp.raw_response.content
    # Count words (excluding stop words)

    # === REQUIREMENT #5: Detect and avoid dead URLs (200 status but no data) ===
    if resp.status != 200:
        return []
    
    if resp.raw_response is None:
        return []
    
    try:
        content = resp.raw_response.content
        if not content or len(content) == 0:
            return []  # Dead URL with no data
    except:
        return []
    
    # Basic content size checks
    if len(content) < 100:  # Too small to have real content
        return []
    
    # === REQUIREMENT #6: Avoid crawling very large files ===
    if len(content) > 5 * 1024 * 1024:  # 5MB limit
        return []
    
    # Defragment URL before checking trap
    defragged_url, _ = urldefrag(url)
    
    # === REQUIREMENT #3: Detect infinite traps ===
    if is_url_trap(defragged_url):
        return []
    
    # Parse HTML
    try:
        soup = BeautifulSoup(content, 'lxml')
    except:
        return []
    
    # Remove script and style elements
    for script in soup(["script", "style"]):
        script.decompose()
    
    # Extract text and count words
    text = soup.get_text()
    words = re.findall(r'\b[a-z]+\b', text.lower())
    
    # === REQUIREMENT #2: High textual information content ===
    if len(words) < 100:  # Page has too few words
        return []
    
    # Track analytics (only for unique pages we actually crawl)
    if defragged_url not in analytics['unique_urls']:
        analytics['unique_urls'].add(defragged_url)

        for word in words:
            if word not in STOP_WORDS:
                analytics['word_counts'][word] += 1
        
        # Track longest page
        if len(words) > analytics['longest_page']['word_count']:
            analytics['longest_page'] = {
                'url': defragged_url,
                'word_count': len(words)
            }
        
        # Track subdomains
        parsed = urlparse(defragged_url)
        if 'uci.edu' in parsed.netloc:
            subdomain = parsed.netloc
            if subdomain not in analytics['subdomains']:
                analytics['subdomains'][subdomain] = 0
            analytics['subdomains'][subdomain] += 1
        
        # Periodically save analytics (every 100 pages)
        if len(analytics['unique_urls']) % 100 == 0:
            save_analytics()
            print(f"✅ Progress: {len(analytics['unique_urls'])} unique pages crawled")
    
    # Extract all links
    links = []
    for link in soup.find_all('a', href=True):
        href = link['href']
        try:
            # Convert relative URLs to absolute
            absolute_url = urljoin(resp.url, href)
            # Defragment URL
            defragged, _ = urldefrag(absolute_url)
            links.append(defragged)
        except (ValueError, Exception) as e:
            # Skip malformed URLs (like placeholders with YOUR_IP, etc.)
            continue
    
    
    return links

def is_valid(url):
    # Decide whether to crawl this url or not. 
    # If you decide to crawl it, return True; otherwise return False.
    # There are already some conditions that return False.
    try:
        parsed = urlparse(url)
        if parsed.scheme not in set(["http", "https"]):
            return False
        # Check if URL is in allowed domains
        # Use word boundary or dot to ensure exact subdomain match
        allowed_domains = [
            r'.*\.ics\.uci\.edu$',      # Requires dot before ics (e.g., www.ics.uci.edu, sub.ics.uci.edu)
            r'^ics\.uci\.edu$',          # OR exactly ics.uci.edu
            r'.*\.cs\.uci\.edu$',        # Requires dot before cs
            r'^cs\.uci\.edu$',           # OR exactly cs.uci.edu
            r'.*\.informatics\.uci\.edu$',
            r'^informatics\.uci\.edu$',
            r'.*\.stat\.uci\.edu$',
            r'^stat\.uci\.edu$'
        ]
        
        domain_match = any(re.match(pattern, parsed.netloc) for pattern in allowed_domains)
        if not domain_match:
            return False
        
        # Avoid certain file extensions
        if re.match(
            r".*\.(css|js|bmp|gif|jpe?g|ico"
            + r"|png|tiff?|mid|mp2|mp3|mp4"
            + r"|wav|avi|mov|mpeg|ram|m4v|mkv|ogg|ogv|pdf"
            + r"|ps|eps|tex|ppt|pptx|doc|docx|xls|xlsx|names"
            + r"|data|dat|exe|bz2|tar|msi|bin|7z|psd|dmg|iso"
            + r"|epub|dll|cnf|tgz|sha1"
            + r"|thmx|mso|arff|rtf|jar|csv"
            + r"|rm|smil|wmv|swf|wma|zip|rar|gz)$", parsed.path.lower()):
            return False
        
        # Avoid common traps
        # Avoid URLs with too many path segments (potential trap)
        if len(parsed.path.split('/')) > 15:
            return False
        
        # Check query parameters safely
        # In is_valid() function, replace the doku.php check with:
        if parsed.query:
            query_lower = parsed.query.lower()
            # Block calendar export formats
            if 'ical' in query_lower or 'outlook' in query_lower:
                return False
            # Block wiki metadata and action pages (not content)
            if 'do=' in query_lower:  # Blocks do=diff, do=revisions, do=backlink, etc.
                return False
            # Block old revision views
            if 'rev=' in query_lower:  # Blocks rev=1234567890
                return False
            # Block wiki comparison pages
            if 'rev2' in query_lower or 'difftype' in query_lower:
                return False
            # Block event display parameters that create duplicates
            if 'eventdisplay' in query_lower or 'event' in query_lower:
                return False
        # Avoid URLs that are too long
        if len(url) > 200:
            return False
        
        # Avoid calendar URLs (common trap)
        if 'calendar' in parsed.path.lower():
            return False
        
        # Only check for suspicious repetitive patterns, not all duplicates
        path_lower = parsed.path.lower()
        # Check for patterns like /dir/dir/dir/ or repeating segments
        segments = [s for s in parsed.path.split('/') if s]  # Remove empty segments
        if len(segments) > 2:
            # Check if same segment repeats more than 2 times
            from collections import Counter
            segment_counts = Counter(segments)
            if any(count > 2 for count in segment_counts.values()):
                return False
        
        # Avoid query strings with many parameters (potential trap)
        if parsed.query:
            params = parsed.query.split('&')
            if len(params) > 5:
                return False
        
        return True
        
    except TypeError:
        print("TypeError for", parsed)
        raise

def save_analytics():
    #saves crawler's analysis results into json file
    with open('analytics.json', 'w') as f:
        json.dump({
            'unique_pages': len(analytics['unique_urls']),
            'longest_page': analytics['longest_page'],
            'top_50_words': analytics['word_counts'].most_common(50),
            'subdomains': dict(sorted(analytics['subdomains'].items()))
        }, f, indent=2)
